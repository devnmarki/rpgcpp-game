#ifndef PHYSICSSYSTEM_HPP
#define PHYSICSSYSTEM_HPP

#include <unordered_set>

#include <box2d/box2d.h>

#include "ecs/system.hpp"
#include "utils/physics_utils.hpp"
#include "utils/collision_utils.hpp"
#include "ecs/entity.hpp"
#include "collision_events.hpp"

class PhysicsSystem : public System {
public:
	PhysicsSystem(World* world, SystemPhase phase = SystemPhase::Update);

	void tick(float dt) override;

private:
	void stepWorld(float dt);
	void initBodies();
	void createBoxCollider(Entity entity, TransformComponent& transform, BoxColliderComponent& boxCollider);
	void updateRigidBodies();
	void syncTransforms();

	void processCollisionEvents();
	void dispatchCollisionEvents();

	Entity getEntityFromShape(b2ShapeId shapeId);

private:
	struct ContactKey {
		Entity a;
		Entity b;

		bool operator==(const ContactKey& other) const {
			return (a == other.a && b == other.b) || (a == other.b && b == other.a);
		}
	}; 

	struct ContactKeyHash {
		size_t operator()(const ContactKey& k) const {
			uint32_t idA = static_cast<uint32_t>(k.a.getId());
			uint32_t idB = static_cast<uint32_t>(k.b.getId());

			return std::hash<uint32_t>()(idA) ^ (std::hash<uint32_t>()(idB) << 1);
		}
	};

	std::unordered_set<ContactKey, ContactKeyHash> m_currentContacts;
	std::unordered_set<ContactKey, ContactKeyHash> m_currentTriggers;
};

#endif