#ifndef CAMERASYSTEM_HPP
#define CAMERASYSTEM_HPP

#include <algorithm>

#include "ecs/system.hpp"
#include "core/input.hpp"

class CameraSystem : public System {
public:
	CameraSystem(World* world, SystemPhase phase = SystemPhase::Update);

	void tick(float dt) override;
};

#endif