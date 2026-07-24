#ifndef APP_HPP
#define APP_HPP

#include <iostream>
#include <string>

#include <SDL3/SDL.h>

#include "window.hpp"
#include "utils/time.hpp"
#include "graphics/renderer.hpp"
#include "loader/asset_loader.hpp"
#include "scene_manager.hpp"

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
	Renderer& getRenderer() { return *m_pRenderer; }
	AssetLoader& getAssetLoader() { return *m_pAssetLoader; }
	SceneManager& getSceneManager() { return *m_pSceneManager; }

protected:
	virtual void onLoad() {}
	virtual void onUpdate() {}
	virtual void onRender() {}

private:
	AppSpecs m_specs;

	bool m_running;

	std::unique_ptr<Window> m_pWindow;
	std::unique_ptr<Time> m_pTime;
	std::unique_ptr<Renderer> m_pRenderer;
	std::unique_ptr<AssetLoader> m_pAssetLoader;
	std::unique_ptr<SceneManager> m_pSceneManager;
};

#endif