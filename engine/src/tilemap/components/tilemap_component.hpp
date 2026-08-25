#ifndef TILEMAPCOMPONENT_HPP
#define TILEMAPCOMPONENT_HPP

#include <string>

struct TilemapComponent {
	std::string tilemapId = "";
	std::string colliderLayerName = "";
	bool collidersInitialized = false;
};

#endif