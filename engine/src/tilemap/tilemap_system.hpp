#ifndef TILEMAPSYSTEM_HPP
#define TILEMAPSYSTEM_HPP

#include "ecs/system.hpp"

#include <tmxlite/Object.hpp>

class TilemapSystem : public System {
public:
	TilemapSystem(World* world, SystemPhase phase = SystemPhase::Update);

	void tick(float dt) override;

private:
	void loadColliders();
	void loadEntities();

	std::vector<tmx::Object> getObjects(TilemapComponent& tilemap, const std::string& layerId);
};

#endif