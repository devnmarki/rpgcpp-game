#ifndef TRIGGERENTITY_HPP
#define TRIGGERENTITY_HPP

#include <glm/glm.hpp>

#include "ecs/world.hpp"
#include "gconstants.hpp"
#include "components.hpp"

class TriggerEntity {
public:
	static Entity create(World& world, const glm::vec2& position) {
		Entity entity = world.createEntity();

		entity.addComponent<TransformComponent>(
			TransformComponent{
				.position = position,
				.scale = global::GAME_SCALE_V
			}
		);
		entity.addComponent<BoxColliderComponent>(
			BoxColliderComponent{
				.size = glm::vec2(16.f * global::GAME_SCALE),
				.isTrigger = true
			}
		);

		return entity;
	}
};

#endif