#include "texture.hpp"
#include "core/app.hpp"

Texture::Texture(const std::string& path)
{
	m_pHandle = IMG_LoadTexture(App::getInstance().getWindow().getRenderer(), path.c_str());
	if (!m_pHandle) {
		spdlog::error("Failed to load texture '{}'!", path);
		return;
	}
	spdlog::info("Created texture '{}' successfully!", path);

	SDL_SetTextureScaleMode(m_pHandle, SDL_SCALEMODE_NEAREST);
	SDL_GetTextureSize(m_pHandle, &m_width, &m_height);
}

Texture::~Texture()
{
	if (m_pHandle)
		SDL_DestroyTexture(m_pHandle);
}