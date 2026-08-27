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

	Texture* spriteTexture = App::getInstance().getAssetLoader().get<Texture>(sprite->getTextureId());
	if (!spriteTexture)
		return;	

	float srcW = sprite->getSource().has_value() ? sprite->getSource()->w : static_cast<float>(spriteTexture->getWidth());
	float srcH = sprite->getSource().has_value() ? sprite->getSource()->h : static_cast<float>(spriteTexture->getHeight());

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
	if (sprite->isFlipX() && sprite->isFlipY())
		flipMode = SDL_FLIP_HORIZONTAL_AND_VERTICAL;
	else if (sprite->isFlipX())
		flipMode = SDL_FLIP_HORIZONTAL;
	else if (sprite->isFlipY())
		flipMode = SDL_FLIP_VERTICAL;

	auto srcOpt = sprite->getSource();
	const SDL_FRect* pSrcRect = srcOpt.has_value() ? &srcOpt.value() : nullptr;

	SDL_RenderTextureRotated(m_pHandle, spriteTexture->getHandle(), pSrcRect, &dst, rotation, &center, flipMode);
}

void Renderer::drawSprite(const Sprite* sprite, const TransformComponent& transform)
{
	drawSprite(sprite, transform.position, transform.scale, transform.rotation);
}

void Renderer::drawRect(const glm::vec2& position, const glm::vec2& size, const Color& color, CameraComponent* cam)
{
	glm::vec2 renderPosition = cam ? worldToScreen(position, *cam) : position;

	SDL_FRect rect = {
		renderPosition.x,
		renderPosition.y,
		size.x,
		size.y
	};

	SDL_SetRenderDrawColor(m_pHandle, color.r, color.g, color.b, color.a);
	SDL_RenderRect(m_pHandle, &rect);
}

void Renderer::fillRect(const glm::vec2& position, const glm::vec2& size, const Color& color, CameraComponent* cam)
{
	glm::vec2 renderPosition = cam ? worldToScreen(position, *cam) : position;

	SDL_FRect rect = {
		renderPosition.x,
		renderPosition.y,
		size.x,
		size.y
	};

	SDL_SetRenderDrawColor(m_pHandle, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(m_pHandle, &rect);
}