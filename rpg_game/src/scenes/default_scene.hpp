#ifndef DEFAULTSCENE_HPP
#define DEFAULTSCENE_HPP

#include "core/engine.hpp"

class DefaultScene : public Scene {
public:
	DefaultScene() = default;

	void onEnter() override;
};

#endif