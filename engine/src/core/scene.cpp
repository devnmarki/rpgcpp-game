#include "scene.hpp"
#include "app.hpp"

Scene::Scene()
{
	m_pWorld = std::make_unique<World>();
	createPhysicsWorld();
}

void Scene::resetWorld(AccessKey)
{
	if (B2_IS_NON_NULL(m_physicsWorldId)) {
		b2DestroyWorld(m_physicsWorldId);
		m_physicsWorldId = b2_nullWorldId;
	}

	createPhysicsWorld();
	m_pWorld = std::make_unique<World>();
}

void Scene::createPhysicsWorld()
{
	const AppSpecs& appSpecs = App::getInstance().getSpecs();

	m_physicsWorldDef = b2DefaultWorldDef();
	m_physicsWorldDef.gravity = b2Vec2{ 0.0f, appSpecs.gravityScale };
	m_physicsWorldId = b2CreateWorld(&m_physicsWorldDef);
}

App& Scene::getApp()
{
	return App::getInstance();
}

Window& Scene::getWindow()
{
	return App::getInstance().getWindow();
}

Renderer& Scene::getRenderer()
{
	return App::getInstance().getRenderer();
}

AssetLoader& Scene::getAssetLoader()
{
	return App::getInstance().getAssetLoader();
}

SceneManager& Scene::getSceneManager()
{
	return App::getInstance().getSceneManager();
}