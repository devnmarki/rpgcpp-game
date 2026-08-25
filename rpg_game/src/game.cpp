#include "game.hpp"

Game::Game()
	: App{ AppSpecs{ "RPG Game | v0.0.1", WindowSpecs{ "", 1280, 720 } } }
{
	getAssetLoader().loadGroup<Texture>("res/data/textures.json");
	getAssetLoader().loadGroup<Sprite>("res/data/sprites.json");
	getAssetLoader().loadGroup<SpriteSheet>("res/data/sprite_sheets.json");
	getAssetLoader().loadGroup<Tilemap>("res/data/tilemaps.json");

	getAssetLoader().loadGroup<AnimationGroup>("res/data/animations/player_animations.json");
	getAssetLoader().loadGroup<AnimationGroup>("res/data/animations/cool_character_animations.json");

	PrefabFactory::add<PlayerPrefab>("player");
	PrefabFactory::add<TriggerPrefab>("trigger");

	getSceneManager().addScene<DefaultScene>("default_scene");
	getSceneManager().addScene<IslandScene>("island_scene");
	getSceneManager().switchScene("default_scene");
}

void Game::onUpdate()
{
	if (Input::isKeyPressed(Keys::Q))
		getSceneManager().switchScene("default_scene");
	else if (Input::isKeyPressed(Keys::E))
		getSceneManager().switchScene("island_scene");
}

void Game::onRender()
{
	
}