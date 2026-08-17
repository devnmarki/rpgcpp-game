#include "movement_system.hpp"

MovementSystem::MovementSystem(World* world, SystemPhase phase)
	: System(world, phase)
{

}

void MovementSystem::tick(float dt)
{
	getWorld()->query<TransformComponent, MovementComponent>([&](Entity entity, TransformComponent& transform, MovementComponent& movement) {
		transform.position += movement.velocity * movement.movementSpeed * dt;
	});

	getWorld()->query<MovementComponent, InputComponent>([](Entity entity, MovementComponent& movement, InputComponent& input) {
		float vx = input.moveRight - input.moveLeft;
		float vy = input.moveDown - input.moveUp;
		glm::vec2 inputDir = glm::vec2(vx, vy);

		movement.isMoving = vx != 0.0f || vy != 0.0f;

		if (glm::length(inputDir) > 0.0f)
			inputDir = glm::normalize(inputDir); 

		movement.velocity = inputDir;
	});

	getWorld()->query<DirectionComponent, MovementComponent, CardinalMovementTag>
		([](Entity entity, DirectionComponent& direction, MovementComponent& movement) {
		Directions prevDirection = direction.direction;

		if (movement.velocity.x > 0.0f) {
			direction.direction = Directions::Right;
		}
		else if (movement.velocity.x < 0.0f) {
			direction.direction = Directions::Left;
		}
		else if (movement.velocity.y > 0.0f) {
			direction.direction = Directions::Down;
		}
		else if (movement.velocity.y < 0.0f) {
			direction.direction = Directions::Up;
		}

		std::string animState = movement.isMoving ? "walk" : "idle";

		bool directionChanged = direction.direction != prevDirection;
		bool movementStateChanged = movement.isMoving != movement.wasMoving;

		if (directionChanged || movementStateChanged) {
			entity.addComponent<AnimationSwitchComponent>(AnimationSwitchComponent{
				.nextAnimation = animState + "_" + DIRECTION_TO_STRING.at(direction.direction)
				});
		}

		movement.wasMoving = movement.isMoving;
	});
}
