#include "movement_system.hpp"

MovementSystem::MovementSystem(World* world, SystemPhase phase)
	: System(world, phase)
{

}

void MovementSystem::tick(float dt)
{
	getWorld()->query<MovementComponent, InputComponent, RigidBodyComponent>
		([](Entity entity, MovementComponent& movement, InputComponent& input, RigidBodyComponent& rigidBody) 
	{
		float vx = input.moveRight - input.moveLeft;
		float vy = input.moveDown - input.moveUp;
		glm::vec2 inputDir = { vx, vy };

		if (glm::length(inputDir) > 0.f)
			inputDir = glm::normalize(inputDir);

		rigidBody.velocity = inputDir * movement.movementSpeed;
		movement.velocity = rigidBody.velocity;

		movement.isMoving = movement.velocity != glm::vec2(0.f);
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

	CameraComponent* cameraComp = nullptr;
	if (!cameraComp) {
		getWorld()->query<CameraComponent>([&](Entity, CameraComponent& camQuery) {
			cameraComp = &camQuery;
		});
	}

	if (cameraComp) {
		getWorld()->query<PlayerTag, TransformComponent>([&](Entity, TransformComponent& transform) {
			cameraComp->target = &transform;
		});
	}
}
