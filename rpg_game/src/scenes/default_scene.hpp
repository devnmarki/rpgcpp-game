#ifndef DEFAULTSCENE_HPP
#define DEFAULTSCENE_HPP

#include "core/engine.hpp"

#include "movement_system.hpp"
#include "input_system.hpp"
#include "player_prefab.hpp"
#include "trigger_prefab.hpp"

class DefaultScene : public Scene {
public:
	DefaultScene() = default;

	void initSystems() override;
	void onEnter() override;
	void onUpdate() override;
};

#endif