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
	stepWorld();
	syncTransforms();
}

void PhysicsSystem::stepWorld()
{
	constexpr float timeStep = 1.0f / 60.0f;
	constexpr int subStepCount = 4;
	
	Scene* activeScene = App::getInstance().getSceneManager().getActiveScene();
	if (!activeScene)
		return;

	b2World_Step(activeScene->getPhysicsWorldId(), timeStep, subStepCount);
}

void PhysicsSystem::initBodies()
{
	getWorld()->query<TransformComponent, BoxColliderComponent>
		([&](Entity entity, TransformComponent& transform, BoxColliderComponent& boxCollider) {
		if (boxCollider.hasBody())
			return;

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

	b2BodyId bodyId = b2CreateBody(worldId, &bodyDef);

	float halfWidth = PhysicsUtils::toMeters(boxCollider.size.x) * 0.5f;
	float halfHeight = PhysicsUtils::toMeters(boxCollider.size.y) * 0.5f;

	b2Polygon box = b2MakeBox(halfWidth, halfHeight);

	b2ShapeDef shapeDef = b2DefaultShapeDef();
	shapeDef.density = isDynamic ? 1.0f : 0.0f;
	shapeDef.isSensor = boxCollider.isTrigger;

	shapeDef.enableContactEvents = true;

	b2CreatePolygonShape(bodyId, &shapeDef, &box);

	boxCollider.bodyId = bodyId;
}

void PhysicsSystem::syncTransforms()
{
	getWorld()->query<TransformComponent, BoxColliderComponent>(
		[](Entity, TransformComponent& transform, BoxColliderComponent& boxCollider) {
		if (!boxCollider.hasBody())
			return;

		b2Vec2 pos = b2Body_GetPosition(boxCollider.bodyId);
		float angle = b2Rot_GetAngle(b2Body_GetRotation(boxCollider.bodyId));

		transform.position = PhysicsUtils::toPixels(glm::vec2(pos.x, pos.y)) - boxCollider.offset;
		transform.rotation = angle * (180.0f / B2_PI);
	});
}