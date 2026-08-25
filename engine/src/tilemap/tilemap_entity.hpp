#ifndef TILEMAPENTITY_HPP
#define TILEMAPENTITY_HPP

#include "ecs/entity.hpp"
#include "tilemap.hpp"
#include "ecs/components.hpp"
#include "ecs/world.hpp"

class TilemapEntity {
public:
	struct Specs {
		std::string tilemapId;
		glm::vec2 scale = glm::vec2(1.0f);
		std::string colliderLayerName = "";
	};

	static Entity create(World& world, const Specs& specs) {
		Entity etilemap = world.createEntity();

		etilemap.addComponent<TransformComponent>(TransformComponent{
			.scale = specs.scale
		});
		etilemap.addComponent<TilemapComponent>(TilemapComponent{
			.tilemapId = specs.tilemapId,
			.colliderLayerName = specs.colliderLayerName
		});

		return etilemap;
	}
};

#endif