#include "game.hpp"

Game::Game()
	: App{ AppSpecs{ "RPG Game | v0.0.1", WindowSpecs{ "", 1280, 720} } }
{
	getAssetLoader().loadTexture("character_base_sheet", "res/textures/entities/character_base_sheet.png");
}

void Game::onRender()
{
	SDL_FRect src = { 0, 0, 32, 32 };
	static float x = 100.0f;
	x += 1.0f;
	getRenderer().drawTexture(getAssetLoader().getTexture("character_base_sheet"), {x, 100}, &src, {4, 4});
}