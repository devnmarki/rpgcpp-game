#include "default_scene.hpp"

void DefaultScene::initSystems()
{
	getWorld().addSystem<MovementSystem>();
	getWorld().addSystem<InputSystem>();
	getWorld().addSystem<TriggerSystem>();
}

void DefaultScene::onEnter()
{
	spdlog::info("Default Scene started!");

	TilemapPrefab tilemapPrefab;
	tilemapPrefab.tilemapId = "tilemap:test_island";
	tilemapPrefab.scale = global::GAME_SCALE_V;
	tilemapPrefab.colliderLayerId = "colliders";
	tilemapPrefab.entityLayerId = "entities";
	tilemapPrefab.build(getWorld(), { 0.f, 0.f });
}

void DefaultScene::onUpdate()
{

}
