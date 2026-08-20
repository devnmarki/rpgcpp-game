#ifndef PHYSICSSYSTEM_HPP
#define PHYSICSSYSTEM_HPP

#include <box2d/box2d.h>

#include "ecs/system.hpp"

class PhysicsSystem : public System {
public:
	PhysicsSystem(World* world, SystemPhase phase = SystemPhase::Update);

	void tick(float dt) override;
};

#endif