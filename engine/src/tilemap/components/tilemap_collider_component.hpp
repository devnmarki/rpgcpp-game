#ifndef TILEMAPCOLLIDERCOMPONENT_HPP
#define TILEMAPCOLLIDERCOMPONENT_HPP

#include <string>

struct TilemapColliderComponent {
	std::string layerId = "";
	bool initialized = false;
};

#endif