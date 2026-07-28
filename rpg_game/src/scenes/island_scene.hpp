#ifndef ISLANDSCENE_HPP
#define ISLANDSCENE_HPP

#include "core/engine.hpp"

class IslandScene : public Scene {
public:
	IslandScene() = default;

	void onEnter() override;
};

#endif