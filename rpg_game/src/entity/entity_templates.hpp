#ifndef ENTITYTEMPLATES_HPP
#define ENTITYTEMPLATES_HPP

#include "core/engine.hpp"

#include "gconstants.hpp"
#include "components.hpp"

class EntityTemplates {
public:
	static Entity createPlayer(World& world, const glm::vec2& position) {
		Entity eplayer = world.createEntity();
		
		eplayer.addComponent<TransformComponent>(
			TransformComponent{ 
				.position = position,
				.scale = global::GAME_SCALE_V
			}
		);
		eplayer.addComponent<SpriteRendererComponent>(
			SpriteRendererComponent{
				.spriteId = "sprite:cool_character_down"
			}
		);
		eplayer.addComponent<MovementComponent>(
			MovementComponent{
				.movementSpeed = 200.0f
			}
		);
		eplayer.addComponent<InputComponent>();

		return eplayer;
	}
};

#endif