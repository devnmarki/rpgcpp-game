#ifndef SCENE_HPP
#define SCENE_HPP

#include "window.hpp"
#include "loader/asset_loader.hpp"
#include "graphics/renderer.hpp"
#include "ecs/world.hpp"

class App;
class SceneManager;

class Scene {
public:
	Scene();
	virtual ~Scene() = default;

	virtual void onEnter() {}
	virtual void onUpdate() {}
	virtual void onRender() {}
	virtual void onExit() {}

	World& getWorld() { return *m_pWorld; }

protected:
	App& getApp();
	Window& getWindow();
	Renderer& getRenderer();
	AssetLoader& getAssetLoader();
	SceneManager& getSceneManager();

private:
	std::unique_ptr<World> m_pWorld;
};

#endif