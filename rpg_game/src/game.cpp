#include "game.hpp"

Game::Game()
	: App{ AppSpecs{ "RPG Game | v0.0.1", WindowSpecs{ "", 1280, 720} } }
{
	m_pTexture = std::make_shared<Texture>("res/textures/cool_character.png");
}
