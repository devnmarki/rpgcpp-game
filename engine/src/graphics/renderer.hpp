#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <optional>

#include <SDL3/SDL.h>
#include <glm/vec2.hpp>

#include "texture.hpp"
#include "sprite.hpp"
#include "ecs/components.hpp"

class Renderer {
public:
	Renderer();

	void drawTexture(
		const Texture* texture, 
		const glm::vec2& pos, 
		const SDL_FRect* src = nullptr, 
		const glm::vec2& scale = { 1.0f, 1.0f }
	);

	void drawSprite(
		const Sprite* sprite,
		const glm::vec2& pos,
		const glm::vec2& scale = { 1.0f, 1.0f },
		float rotation = 0.0f
	);

	void drawSprite(
		const Sprite* sprite,
		const TransformComponent& transform
	);

	SDL_Renderer* getHandle() { return m_pHandle; }

private:
	SDL_Renderer* m_pHandle;
};

#endif