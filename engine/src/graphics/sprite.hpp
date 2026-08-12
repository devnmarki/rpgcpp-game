#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <optional>
#include <string>

#include <SDL3/SDL.h>

struct Sprite {
	std::string textureId = "";
	std::optional<SDL_FRect> src = std::nullopt;
	bool flipX = false;
	bool flipY = false;
};

#endif