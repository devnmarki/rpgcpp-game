#ifndef APP_HPP
#define APP_HPP

#include <iostream>
#include <string>

#include <SDL3/SDL.h>
#include <tmxlite/Map.hpp>

#include "window.hpp"
#include "utils/time.hpp"
#include "graphics/renderer.hpp"
#include "loader/asset_loader.hpp"
#include "scene_manager.hpp"
#include "input.hpp"
#include "loader/animation_storage.hpp"
#include "utils/debug.hpp"

struct AppSpecs {
	std::string name;
	WindowSpecs windowSpecs;
	float gravityScale = 10.0f;
};

class App {
public:
	App(const AppSpecs& specs);
	virtual ~App();

	void run();

	static App& getInstance();

	const AppSpecs& getSpecs() const { return m_specs; }
	Window& getWindow() const { return *m_pWindow; }
	Renderer& getRenderer() { return *m_pRenderer; }
	AssetLoader& getAssetLoader() { return *m_pAssetLoader; }
	SceneManager& getSceneManager() { return *m_pSceneManager; }
	Time& getTime() { return *m_pTime; }
	AnimationStorage& getAnimationStorage() { return *m_pAnimationStorage; }

protected:
	virtual void onLoad() {}
	virtual void onUpdate() {}
	virtual void onRender() {}

private:
	AppSpecs m_specs;

	bool m_running;
	bool m_debugMode = false;

	std::unique_ptr<Window> m_pWindow;
	std::unique_ptr<Time> m_pTime;
	std::unique_ptr<Renderer> m_pRenderer;
	std::unique_ptr<AssetLoader> m_pAssetLoader;
	std::unique_ptr<SceneManager> m_pSceneManager;
	std::unique_ptr<AnimationStorage> m_pAnimationStorage;
};

#endif