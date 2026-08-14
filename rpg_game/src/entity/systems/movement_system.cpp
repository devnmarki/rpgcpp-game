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

		if (glm::length(inputDir) > 0.0f)
			inputDir = glm::normalize(inputDir);

		movement.velocity = inputDir;
	});
}
