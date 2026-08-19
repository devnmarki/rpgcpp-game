#ifndef TILEMAPENTITY_HPP
#define TILEMAPENTITY_HPP

#include "ecs/entity.hpp"
#include "tilemap.hpp"
#include "ecs/components.hpp"
#include "ecs/world.hpp"

class TilemapEntity {
public:
	static Entity create(World& world, const std::string& tilemapId, const glm::vec2& scale = glm::vec2(1.0f)) {
		Entity etilemap = world.createEntity();

		etilemap.addComponent<TransformComponent>(TransformComponent{
			.scale = scale
		});
		etilemap.addComponent<TilemapComponent>(TilemapComponent{
			.tilemapId = tilemapId
		});

		return etilemap;
	}
};

#endif