#ifndef GAME_HPP
#define GAME_HPP

#include "core/engine.hpp"

#include "scenes/scenes.hpp"

class Game : public App {
public:
	Game();

	void onUpdate() override;
	void onRender() override;
};

#endif