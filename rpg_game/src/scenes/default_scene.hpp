#ifndef DEFAULTSCENE_HPP
#define DEFAULTSCENE_HPP

#include "core/engine.hpp"

#include "player_entity.hpp"
#include "trigger_entity.hpp"
#include "movement_system.hpp"
#include "input_system.hpp"

class DefaultScene : public Scene {
public:
	DefaultScene() = default;

	void onEnter() override;
	void onUpdate() override;
};

#endif