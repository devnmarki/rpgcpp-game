#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>

#include "window.hpp"
#include "loader/asset_loader.hpp"
#include "graphics/renderer.hpp"
#include "ecs/world.hpp"
#include "ecs/system.hpp"

class App;
class SceneManager;

class Scene {
private:
	struct AccessKey {
		explicit AccessKey() = default;
	};

public:
	Scene();
	virtual ~Scene() = default;

	virtual void onEnter() {}
	virtual void onUpdate() {}
	virtual void onRender() {}
	virtual void onExit() {}

	void resetWorld(AccessKey);

	World& getWorld() { return *m_pWorld; }

protected:
	App& getApp();
	Window& getWindow();
	Renderer& getRenderer();
	AssetLoader& getAssetLoader();
	SceneManager& getSceneManager();

private:
	std::unique_ptr<World> m_pWorld;

	friend class SceneManager;
};

#endif