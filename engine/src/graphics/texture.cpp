#include "texture.hpp"
#include "core/app.hpp"

Texture::Texture(const std::string& path)
{
	m_pHandle = IMG_LoadTexture(App::getInstance().getWindow().getRenderer(), path.c_str());
	if (!m_pHandle) {
		std::cout << "[ERROR]: Failed to load texture '" << path << "'" << "! Error: " << SDL_GetError() << std::endl;
		return;
	}
	std::cout << "[INFO]: Texture '" << path << "' loaded successfully!" << std::endl;

	SDL_GetTextureSize(m_pHandle, &m_width, &m_height);
}

Texture::~Texture()
{
	if (m_pHandle)
		SDL_DestroyTexture(m_pHandle);
}