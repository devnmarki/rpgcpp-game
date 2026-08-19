#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include <spdlog/spdlog.h>

#include "ecs/system.hpp"
#include "tilemap/tilemap.hpp"
#include "core/camera_utils.hpp"

class RenderSystem : public System {
public:
	RenderSystem(World* world, SystemPhase phase);

	void tick(float dt) override;

private:
	void renderSprites();
	void renderTilemaps();

	const tmx::Tileset* findTileset(const tmx::Map& map, uint32_t gid);
	CameraComponent* queryCameraComponent();
};

#endif