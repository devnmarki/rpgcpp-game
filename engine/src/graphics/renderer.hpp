#pragma once

#include <optional>

#include <SDL3/SDL.h>
#include <glm/vec2.hpp>

#include "texture.hpp"

class Renderer {
public:
	Renderer();

	void drawTexture(const Texture* texture, const glm::vec2& pos, const SDL_FRect* src = nullptr, const glm::vec2& scale = { 1.0f, 1.0f });

private:
	SDL_Renderer* m_pHandle;
};