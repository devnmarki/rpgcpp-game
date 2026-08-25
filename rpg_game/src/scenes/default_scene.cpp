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

	PlayerPrefab playerPrefab;
	playerPrefab.movementSpeed = 180.f;
	playerPrefab.build(getWorld(), { 400.f, 350.f });

	TriggerPrefab triggerPrefab;
	triggerPrefab.to = "island_scene";
	triggerPrefab.build(getWorld(), { 500.f, 400.f });

	TilemapEntity::create(getWorld(), { "tilemap:test_island", global::GAME_SCALE_V, "colliders" });
}

void DefaultScene::onUpdate()
{

}
