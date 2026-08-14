#ifndef ANIMATIONSYSTEM_HPP
#define ANIMATIONSYSTEM_HPP

#include "ecs/system.hpp"

class AnimationSystem : public System {
public:
	AnimationSystem(World* world, SystemPhase phase = SystemPhase::Update);

	void tick(float dt) override;
};

#endif