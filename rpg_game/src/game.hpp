#pragma once

#include "core/engine.hpp"

class Game : public App {
public:
	Game();

	void onRender() override;

private:
	std::shared_ptr<Texture> m_pTexture;
};