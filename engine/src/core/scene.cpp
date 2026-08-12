#include "scene.hpp"
#include "app.hpp"

Scene::Scene()
{
	m_pWorld = std::make_unique<World>();
}

void Scene::resetWorld(AccessKey)
{
	m_pWorld = std::make_unique<World>();
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