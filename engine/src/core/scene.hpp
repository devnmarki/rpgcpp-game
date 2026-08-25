#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>

#include <box2d/box2d.h>

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

	virtual void initSystems() {}
	virtual void onEnter() {}
	virtual void onUpdate() {}
	virtual void onRender() {}
	virtual void onExit() {}

	void resetWorld(AccessKey);

	World& getWorld() { return *m_pWorld; }
	b2WorldId& getPhysicsWorldId() { return m_physicsWorldId; }
	b2WorldDef& getPhysicsWorldDef() { return m_physicsWorldDef; }
	Entity& getCamera() { return m_cameraEntity; }

protected:
	App& getApp();
	Window& getWindow();
	Renderer& getRenderer();
	AssetLoader& getAssetLoader();
	SceneManager& getSceneManager();

private:
	void createPhysicsWorld();

private:
	std::unique_ptr<World> m_pWorld;
	b2WorldDef m_physicsWorldDef;
	b2WorldId m_physicsWorldId;
	Entity m_cameraEntity;

	friend class SceneManager;
};

#endif