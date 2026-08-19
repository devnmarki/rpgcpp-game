#ifndef ENTITYTEMPLATES_HPP
#define ENTITYTEMPLATES_HPP

#include "core/engine.hpp"

#include "gconstants.hpp"
#include "components.hpp"

class EntityTemplates {
public:
	static Entity createPlayer(World& world, const glm::vec2& position) {
		Entity eplayer = world.createEntity();

		eplayer.addComponent<PlayerTag>();
		eplayer.addComponent<TransformComponent>(
			TransformComponent{ 
				.position = position,
				.scale = global::GAME_SCALE_V
			}
		);
		eplayer.addComponent<SpriteRendererComponent>(
			SpriteRendererComponent{
				.spriteId = App::getInstance().getAssetLoader().get<SpriteSheet>("sheet:cool_character")->getSpriteId(1)
			}
		);
		eplayer.addComponent<MovementComponent>(
			MovementComponent{
				.movementSpeed = 200.0f
			}
		);
		eplayer.addComponent<InputComponent>();
		eplayer.addComponent<AnimatorComponent>(
			AnimatorComponent{
				.groupId = "animation:player",
				.currentAnimationId = "walk_down"
			}
		);
		eplayer.addComponent<DirectionComponent>(
			DirectionComponent{
				.direction = Directions::Down
			}
		);
		eplayer.addComponent<CardinalMovementTag>();

		return eplayer;
	}
};

#endif