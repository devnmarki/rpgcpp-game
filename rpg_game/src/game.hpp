#ifndef GAME_HPP
#define GAME_HPP

#include "core/engine.hpp"

class Game : public App {
public:
	Game();

	void onRender() override;
};

#endif