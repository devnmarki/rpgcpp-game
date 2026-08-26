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

	TriggerPrefab triggerPrefab;
	triggerPrefab.to = "island_scene";
	triggerPrefab.build(getWorld(), { 500.f, 400.f });

	PrefabFactory::create("player", getWorld(), { 400.f, 350.f });

	TilemapPrefab tilemapPrefab;
	tilemapPrefab.tilemapId = "tilemap:test_island";
	tilemapPrefab.colliderLayerId = "colliders";
	tilemapPrefab.scale = global::GAME_SCALE_V;
	tilemapPrefab.build(getWorld(), { 0.f, 0.f });
}

void DefaultScene::onUpdate()
{

}
