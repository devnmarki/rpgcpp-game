#ifndef TILEMAPSYSTEM_HPP
#define TILEMAPSYSTEM_HPP

#include "ecs/system.hpp"

class TilemapSystem : public System {
public:
	TilemapSystem(World* world, SystemPhase phase = SystemPhase::Update);

	void tick(float dt) override;
};

#endif