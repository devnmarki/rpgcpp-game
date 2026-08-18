#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <SDL3/SDL.h>

#include "utils/utils.hpp"

struct WindowSpecs {
	std::string title;
	int width;
	int height;
};

class Window {
public:
	Window(const WindowSpecs& specs);
	~Window();

	void create();

	void beginFrame(const Color& color);
	void endFrame();

	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	std::string getTitle() { return m_specs.title; }
	SDL_Window* getHandle() { return m_pHandle; }
	SDL_Renderer* getRenderer() { return m_pRenderer; }

private:
	WindowSpecs m_specs;

	SDL_Window* m_pHandle;
	SDL_Renderer* m_pRenderer;

	int m_width = 0;
	int m_height = 0;
};

#endif