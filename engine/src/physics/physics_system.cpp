#include "physics_system.hpp"
#include "ecs/world.hpp"
#include "core/app.hpp"

PhysicsSystem::PhysicsSystem(World* world, SystemPhase phase)
	: System(world, phase)
{

}

void PhysicsSystem::tick(float dt)
{
	initBodies();

	updateRigidBodies();

	stepWorld(dt);
	processCollisionEvents();
	syncTransforms();
}

void PhysicsSystem::stepWorld(float dt)
{
	dt = std::min(dt, 0.05f);

	Scene* activeScene = App::getInstance().getSceneManager().getActiveScene();
	if (!activeScene)
		return;

	b2World_Step(activeScene->getPhysicsWorldId(), dt, 4);

	b2WorldId worldId = App::getInstance()
							.getSceneManager()
							.getActiveScene()
							->getPhysicsWorldId();
}

void PhysicsSystem::initBodies()
{
	getWorld()->query<TransformComponent, BoxColliderComponent>
		([&](Entity entity, TransformComponent& transform, BoxColliderComponent& boxCollider) 
	{
		if (boxCollider.hasBody() && b2Body_IsValid(boxCollider.bodyId))
			return;

		boxCollider.bodyId = b2_nullBodyId;

		createBoxCollider(entity, transform, boxCollider);
	});
}

void PhysicsSystem::createBoxCollider(Entity entity, TransformComponent& transform, BoxColliderComponent& boxCollider)
{
	b2WorldId worldId = App::getInstance()
							.getSceneManager()
							.getActiveScene()
						    ->getPhysicsWorldId();

	b2BodyDef bodyDef = b2DefaultBodyDef();

	glm::vec2 pixelPos = transform.position + boxCollider.offset;
	bodyDef.position.x = PhysicsUtils::toMeters(pixelPos.x);
	bodyDef.position.y = PhysicsUtils::toMeters(pixelPos.y);

	bool isDynamic = entity.hasComponent<RigidBodyComponent>();
	bodyDef.type = isDynamic ? b2_dynamicBody : b2_staticBody;

	bodyDef.userData = reinterpret_cast<void*>(static_cast<uintptr_t>(entity.getId()));

	b2BodyId bodyId = b2CreateBody(worldId, &bodyDef);

	float halfWidth = PhysicsUtils::toMeters(boxCollider.size.x) * 0.5f;
	float halfHeight = PhysicsUtils::toMeters(boxCollider.size.y) * 0.5f;

	b2Polygon box = b2MakeBox(halfWidth, halfHeight);

	b2ShapeDef shapeDef = b2DefaultShapeDef();
	shapeDef.density = isDynamic ? 1.0f : 0.0f;
	shapeDef.isSensor = boxCollider.isTrigger;
	shapeDef.enableContactEvents = true;
	shapeDef.enableSensorEvents = true;

	b2CreatePolygonShape(bodyId, &shapeDef, &box);

	boxCollider.bodyId = bodyId;
}

void PhysicsSystem::updateRigidBodies()
{
	getWorld()->query<BoxColliderComponent, RigidBodyComponent>(
		[](Entity, BoxColliderComponent& collider, RigidBodyComponent& rigidBody) 
	{
		if (!collider.hasBody() || !b2Body_IsValid(collider.bodyId)) {
			collider.bodyId = b2_nullBodyId;
			return;
		}

		b2BodyId body = collider.bodyId;
		
		b2Vec2 vel = PhysicsUtils::toMeters(b2Vec2{rigidBody.velocity.x, rigidBody.velocity.y });
		b2Body_SetLinearVelocity(body, vel);

		b2MassData massData = { rigidBody.mass };
		b2Body_SetMassData(body, massData);

		b2Body_SetGravityScale(body, rigidBody.gravityScale);
	});
}

void PhysicsSystem::syncTransforms()
{
	getWorld()->query<TransformComponent, BoxColliderComponent>(
		[](Entity, TransformComponent& transform, BoxColliderComponent& boxCollider) 
	{
		if (!boxCollider.hasBody() || !b2Body_IsValid(boxCollider.bodyId)) {
			boxCollider.bodyId = b2_nullBodyId;
			return;
		}

		b2Vec2 pos = b2Body_GetPosition(boxCollider.bodyId);
		float angle = b2Rot_GetAngle(b2Body_GetRotation(boxCollider.bodyId));

		transform.position = PhysicsUtils::toPixels(glm::vec2(pos.x, pos.y)) - boxCollider.offset;
		transform.rotation = angle * (180.0f / B2_PI);
	});
}

void PhysicsSystem::processCollisionEvents()
{
	g_collisionEvents.clear();

	Scene* scene = App::getInstance().getSceneManager().getActiveScene();
	if (!scene)
		return;

	b2WorldId worldId = scene->getPhysicsWorldId();

	// -----------------------------
	// Regular contacts (collisions)
	// -----------------------------
	b2ContactEvents contactEvents = b2World_GetContactEvents(worldId);

	for (int i = 0; i < contactEvents.beginCount; i++) {
		auto* e = contactEvents.beginEvents + i;
		Entity a = getEntityFromShape(e->shapeIdA);
		Entity b = getEntityFromShape(e->shapeIdB);

		if (!a.isValid() || !b.isValid())
			continue;

		ContactKey key{ a, b };
		m_currentContacts.insert(key);

		g_collisionEvents.push_back({ CollisionType::Enter, a, b, false });
		g_collisionEvents.push_back({ CollisionType::Enter, b, a, false });
	}

	for (int i = 0; i < contactEvents.endCount; i++) {
		auto* e = contactEvents.endEvents + i;
		Entity a = getEntityFromShape(e->shapeIdA);
		Entity b = getEntityFromShape(e->shapeIdB);

		if (!a.isValid() || !b.isValid())
			continue;

		ContactKey key{ a, b };
		m_currentContacts.erase(key);

		g_collisionEvents.push_back({ CollisionType::Exit, a, b, false });
		g_collisionEvents.push_back({ CollisionType::Exit, b, a, false });
	}

	// -----------------------------
	// Sensors (triggers)
	// -----------------------------
	b2SensorEvents sensorEvents = b2World_GetSensorEvents(worldId);

	for (int i = 0; i < sensorEvents.beginCount; i++) {
		auto* e = sensorEvents.beginEvents + i;
		Entity a = getEntityFromShape(e->sensorShapeId);
		Entity b = getEntityFromShape(e->visitorShapeId);
		
		if (!a.isValid() || !b.isValid())
			continue;

		ContactKey key{ a, b };
		m_currentTriggers.insert(key);

		g_collisionEvents.push_back({ CollisionType::Enter, a, b, true });
		g_collisionEvents.push_back({ CollisionType::Enter, b, a, true });
	}

	for (int i = 0; i < sensorEvents.endCount; i++) {
		auto* e = sensorEvents.endEvents + i;
		Entity a = getEntityFromShape(e->sensorShapeId);
		Entity b = getEntityFromShape(e->visitorShapeId);

		if (!a.isValid() || !b.isValid())
			continue;

		ContactKey key{ a, b };
		m_currentTriggers.erase(key);

		g_collisionEvents.push_back({ CollisionType::Exit, a, b, true });
		g_collisionEvents.push_back({ CollisionType::Exit, b, a, true });
	}

	// -----------------------------
	// Stay events
	// -----------------------------
	for (const auto& key : m_currentContacts) {
		g_collisionEvents.push_back({ CollisionType::Stay, key.a, key.b, false });
		g_collisionEvents.push_back({ CollisionType::Stay, key.b, key.a, false });
	}
	
	for (const auto& key : m_currentTriggers) {
		g_collisionEvents.push_back({ CollisionType::Stay, key.a, key.b, true });
		g_collisionEvents.push_back({ CollisionType::Stay, key.b, key.a, true });
	}
}

Entity PhysicsSystem::getEntityFromShape(b2ShapeId shapeId)
{
	if (!b2Shape_IsValid(shapeId))
		return Entity{};

	b2BodyId bodyId = b2Shape_GetBody(shapeId);
	if (!b2Body_IsValid(bodyId))
		return Entity{};

	void* userData = b2Body_GetUserData(bodyId);
	if (!userData)
		return Entity{};

	entt::entity eid = static_cast<entt::entity>(
		static_cast<uint32_t>(reinterpret_cast<uintptr_t>(userData)));

	return Entity{ eid, &getWorld()->getRegistry() };
}