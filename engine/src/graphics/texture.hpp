#pragma once

#include <iostream>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class Texture {
public:
	Texture(const std::string& path);
	~Texture();

	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	SDL_Texture* getHandle() { return m_pHandle; }

private:
	float m_width = 0.0f;
	float m_height = 0.0f;
	SDL_Texture* m_pHandle;
};