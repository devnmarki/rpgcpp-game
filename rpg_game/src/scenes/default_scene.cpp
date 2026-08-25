#include "default_scene.hpp"

void DefaultScene::initSystems()
{
	getWorld().addSystem<MovementSystem>();
	getWorld().addSystem<InputSystem>();
}

void DefaultScene::onEnter()
{
	spdlog::info("Default Scene started!");
	
	getCamera().getComponent<CameraComponent>().damping = 100.0f;

	PlayerEntity::create(getWorld(), glm::vec2(400.f, 350.f));
	TriggerEntity::create(getWorld(), glm::vec2(500.f, 400.f));
	TilemapEntity::create(getWorld(), { "tilemap:test_island", global::GAME_SCALE_V, "colliders" });
}

void DefaultScene::onUpdate()
{

}
