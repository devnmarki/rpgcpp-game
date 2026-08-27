#ifndef TRIGGERPREFAB_HPP
#define TRIGGERPREFAB_HPP

#include "core/engine.hpp"
#include "components.hpp"
#include "gconstants.hpp"

class TriggerPrefab : public Prefab {
public:
	glm::vec2 triggerSize = { 16.f, 16.f };
	std::string to = "";

	Entity build(World& world, const glm::vec2& position) const override {
		Entity entity = world.createEntity();

		entity.addComponent<TransformComponent>(
			TransformComponent{
				.position = position,
				.scale = global::GAME_SCALE_V
			}
		);
		entity.addComponent<BoxColliderComponent>(
			BoxColliderComponent{
				.size = triggerSize * global::GAME_SCALE,
				.isTrigger = true
			}
		);
		entity.addComponent<TriggerComponent>(
			TriggerComponent{
				.to = to
			}
		);

		return entity;
	}
};

#endif