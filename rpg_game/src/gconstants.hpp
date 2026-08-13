#ifndef GCONSTANTS_HPP
#define GCONSTANTS_HPP

#include "core/engine.hpp"

namespace global {
	inline const float GAME_SCALE = 4.0f;
	inline const glm::vec2 GAME_SCALE_V = glm::vec2(GAME_SCALE);
	inline const float TILE_SIZE = 16.0f;
	inline const float TILE_SIZE_SCALED = TILE_SIZE * GAME_SCALE;
}

#endif