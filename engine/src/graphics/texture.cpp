#include "texture.hpp"
#include "core/app.hpp"

Texture::Texture(const TextureData& data)
	: m_data(data)
{
	m_pHandle = IMG_LoadTexture(App::getInstance().getWindow().getRenderer(), m_data.path.c_str());
	if (!m_pHandle) {
		spdlog::error("Failed to load texture '{}'!", m_data.path);
		return;
	}

	SDL_SetTextureScaleMode(m_pHandle, SDL_SCALEMODE_NEAREST);
	SDL_GetTextureSize(m_pHandle, &m_width, &m_height);
}

Texture::Texture(const TextureConfig& config)
	: Texture(config.data)
{

}

Texture::~Texture()
{
	if (m_pHandle)
		SDL_DestroyTexture(m_pHandle);
}