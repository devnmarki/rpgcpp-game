#include "input_system.hpp"

InputSystem::InputSystem(World* world, SystemPhase phase)
	: System(world, phase)
{

}

void InputSystem::tick(float dt)
{
	getWorld()->query<InputComponent>([](Entity entity, InputComponent& input) {
		input.moveLeft = Input::isKeyDown(Keys::A);
		input.moveRight = Input::isKeyDown(Keys::D);
		input.moveUp = Input::isKeyDown(Keys::W);
		input.moveDown = Input::isKeyDown(Keys::S);
	});
}
