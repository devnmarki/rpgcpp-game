#ifndef PLAYERPREFAB_HPP
#define PLAYERPREFAB_HPP

#include "core/engine.hpp"
#include "components.hpp"
#include "gconstants.hpp"

class PlayerPrefab : public Prefab {
public:
	float movementSpeed = 200.f;

	Entity build(World& world, const glm::vec2& position) const override {
		Entity entity = world.createEntity();

		entity.addComponent<PlayerTag>();
		entity.addComponent<TransformComponent>(
			TransformComponent{
				.position = position,
				.scale = global::GAME_SCALE_V
			}
		);
		entity.addComponent<SpriteRendererComponent>();
		entity.addComponent<BoxColliderComponent>(
			BoxColliderComponent{
				.size = glm::vec2(9.f, 16.f) * global::GAME_SCALE_V,
			}
			);
		entity.addComponent<RigidBodyComponent>(
			RigidBodyComponent{
				.gravityScale = 0.0f
			}
		);
		entity.addComponent<MovementComponent>(
			MovementComponent{
				.movementSpeed = movementSpeed
			}
		);
		entity.addComponent<InputComponent>();
		entity.addComponent<AnimatorComponent>(
			AnimatorComponent{
				.groupId = "animation:player",
				.currentAnimationId = "walk_down"
			}
		);
		entity.addComponent<DirectionComponent>(
			DirectionComponent{
				.direction = Directions::Down
			}
		);
		entity.addComponent<CardinalMovementTag>();

		return entity;
	}
};

#endif