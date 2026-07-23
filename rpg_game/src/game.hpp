#pragma once

#include "core/engine.hpp"

class Game : public App {
public:
	Game();

private:
	std::shared_ptr<Texture> m_pTexture;
};