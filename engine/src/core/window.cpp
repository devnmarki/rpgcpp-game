#include "window.hpp"

Window::Window(const WindowSpecs& specs)
	: m_specs(specs), m_pHandle(nullptr), m_pRenderer(nullptr)
{

}

Window::~Window()
{
	if (m_pRenderer)
		SDL_DestroyRenderer(m_pRenderer);
	
	if (m_pHandle)
		SDL_DestroyWindow(m_pHandle);
}

void Window::create()
{
	if (!SDL_CreateWindowAndRenderer(m_specs.title.c_str(), m_specs.width, m_specs.height, NULL, &m_pHandle, &m_pRenderer)) {
		std::cout << "Failed to create SDL window! Error: " << SDL_GetError() << std::endl;
	}

	SDL_GetWindowSize(m_pHandle, &m_width, &m_height);
}

void Window::beginFrame(const Color& color = { 0, 0, 0 })
{
	SDL_SetRenderDrawColor(m_pRenderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_pRenderer);
}

void Window::endFrame()
{
	SDL_RenderPresent(m_pRenderer);
}