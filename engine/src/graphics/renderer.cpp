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

void Renderer::drawSprite(const Sprite* sprite, const glm::vec2& pos, const glm::vec2& scale, float rotation)
{
	if (!sprite)
		return;

	Texture* spriteTexture = App::getInstance().getAssetLoader().getTexture(sprite->textureId);
	if (!spriteTexture)
		return;	

	float srcW = sprite->src.has_value() ? sprite->src->w : static_cast<float>(spriteTexture->getWidth());
	float srcH = sprite->src.has_value() ? sprite->src->h : static_cast<float>(spriteTexture->getHeight());

	float scaledW = srcW * scale.x;
	float scaledH = srcH * scale.y;

	SDL_FRect dst = {
		pos.x - (scaledW / 2.0f),
		pos.y - (scaledH / 2.0f),
		scaledW,
		scaledH
	};

	SDL_FPoint center = {
		scaledW / 2.0f,
		scaledH / 2.0f
	};

	SDL_FlipMode flipMode = SDL_FLIP_NONE;
	if (sprite->flipX && sprite->flipY)
		flipMode = SDL_FLIP_HORIZONTAL_AND_VERTICAL;
	else if (sprite->flipX)
		flipMode = SDL_FLIP_HORIZONTAL;
	else if (sprite->flipY)
		flipMode = SDL_FLIP_VERTICAL;

	const SDL_FRect* pSrcRect = sprite->src.has_value() ? &sprite->src.value() : nullptr;

	SDL_RenderTextureRotated(m_pHandle, spriteTexture->getHandle(), pSrcRect, &dst, rotation, &center, flipMode);
}

void Renderer::drawSprite(const Sprite* sprite, const TransformComponent& transform)
{
	drawSprite(sprite, transform.position, transform.scale, transform.rotation);
}