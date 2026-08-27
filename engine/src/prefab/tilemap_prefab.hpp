#ifndef TILEMAPPREFAB_HPP
#define TILEMAPPREFAB_HPP

#include "prefab.hpp"

class TilemapPrefab : public Prefab {
public:
	glm::vec2 scale = { 1.f, 1.f };
	std::string tilemapId = "";
	std::string colliderLayerId = "";
	std::string entityLayerId = "";

	Entity build(World& world, const glm::vec2& position) const override {
		Entity entity = world.createEntity();

		entity.addComponent<TransformComponent>(TransformComponent{
			.position = position,
			.scale = scale
		});
		entity.addComponent<TilemapComponent>(TilemapComponent{
			.tilemapId = tilemapId,
		});

		if (!colliderLayerId.empty()) {
			entity.addComponent<TilemapColliderComponent>(TilemapColliderComponent{
				.layerId = colliderLayerId
			});
		}

		if (!entityLayerId.empty()) {
			entity.addComponent<TilemapSpawnerComponent>(TilemapSpawnerComponent{
				.layerId = entityLayerId
			});
		}

		return entity;
	}
};

#endif