#include "game.hpp"

Game::Game()
	: App{ AppSpecs{ "RPG Game | v0.0.1", WindowSpecs{ "", 1280, 720} } }
{
	m_pTexture = std::make_shared<Texture>("res/textures/cool_character.png");
}

void Game::onRender()
{
	App::onRender();

	SDL_FRect src = { 32, 0, 32, 32 };
	getRenderer().drawTexture(m_pTexture.get(), { 100, 100 }, &src, {3, 3});
}