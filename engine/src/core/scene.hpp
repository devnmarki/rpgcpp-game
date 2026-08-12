#ifndef SCENE_HPP
#define SCENE_HPP

#include "window.hpp"
#include "loader/asset_loader.hpp"
#include "graphics/renderer.hpp"

class App;
class SceneManager;

class Scene {
public:
	Scene() = default;
	virtual ~Scene() = default;

	virtual void onEnter() {}
	virtual void onUpdate() {}
	virtual void onRender() {}
	virtual void onExit() {}

protected:
	App& getApp();
	Window& getWindow();
	Renderer& getRenderer();
	AssetLoader& getAssetLoader();
	SceneManager& getSceneManager();
};

#endif