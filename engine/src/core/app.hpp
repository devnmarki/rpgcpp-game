#pragma once

#include <iostream>
#include <string>

#include <SDL3/SDL.h>

#include "window.hpp"
#include "utils/time.hpp"

struct AppSpecs {
	std::string name;
	WindowSpecs windowSpecs;
};

class App {
public:
	App(const AppSpecs& specs);
	virtual ~App();

	void run();

	static App& getInstance();

	Window& getWindow() const { return *m_pWindow; }

protected:
	virtual void onLoad() {}
	virtual void onUpdate() {}
	virtual void onRender() {}

private:
	AppSpecs m_specs;

	std::unique_ptr<Window> m_pWindow;
	std::unique_ptr<Time> m_pTime;
	bool m_running;
};