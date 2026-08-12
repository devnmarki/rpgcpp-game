#include "game.hpp"

Game::Game()
	: App{ AppSpecs{ "RPG Game | v0.0.1", WindowSpecs{ "", 1280, 720} } }
{
	getAssetLoader().loadTextureGroup("res/data/textures.json");

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