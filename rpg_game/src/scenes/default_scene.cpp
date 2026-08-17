#include "default_scene.hpp"

void DefaultScene::onEnter()
{
	spdlog::info("Default Scene started!");

	getWorld().addSystem<MovementSystem>();
	getWorld().addSystem<InputSystem>();

	EntityTemplates::createPlayer(getWorld(), glm::vec2(400.0f, 350.0f));
}