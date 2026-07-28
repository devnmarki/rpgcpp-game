#include "renderer.hpp"
#include "core/app.hpp"

Renderer::Renderer()
	: m_pHandle(App::getInstance().getWindow().getRenderer())
{

}

void Renderer::drawTexture(const Texture* texture, const glm::vec2& pos, const SDL_FRect* src, const glm::vec2& scale)
{
	if (!texture)
		return;

	SDL_FRect dst = {
		pos.x,
		pos.y,
		!src ? texture->getWidth() * scale.x : src->w * scale.x,
		!src ? texture->getHeight() * scale.y : src->h * scale.y
	};

	SDL_RenderTextureRotated(m_pHandle, texture->getHandle(), src, &dst, 0.0f, nullptr, SDL_FLIP_NONE);
}
