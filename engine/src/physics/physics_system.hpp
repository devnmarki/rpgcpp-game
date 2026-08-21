#ifndef PHYSICSSYSTEM_HPP
#define PHYSICSSYSTEM_HPP

#include <box2d/box2d.h>

#include "ecs/system.hpp"
#include "utils/physics_utils.hpp"
#include "ecs/entity.hpp"

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
};

#endif