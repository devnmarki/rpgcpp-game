#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include <spdlog/spdlog.h>

#include "ecs/system.hpp"

class RenderSystem : public System {
public:
	RenderSystem(World* world, SystemPhase phase);

	void tick(float dt) override;
};

#endif