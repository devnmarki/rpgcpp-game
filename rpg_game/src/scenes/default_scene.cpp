#include "default_scene.hpp"

void DefaultScene::onEnter()
{
	spdlog::info("Default Scene started!");

	getWorld().addSystem<MovementSystem>();
	getWorld().addSystem<InputSystem>();

	getCamera().getComponent<CameraComponent>().damping = 100.0f;

	EntityTemplates::createPlayer(getWorld(), glm::vec2(400.0f, 350.0f));
	TilemapEntity::create(getWorld(), "tilemap:test_island", global::GAME_SCALE_V);
}

void DefaultScene::onUpdate()
{
	//spdlog::info("X: {}, Y: {}", getCamera().getComponent<CameraComponent>().position.x, getCamera().getComponent<CameraComponent>().position.x);
}
