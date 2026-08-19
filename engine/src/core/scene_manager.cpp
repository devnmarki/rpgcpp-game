#include "scene_manager.hpp"

void SceneManager::switchScene(const std::string& id)
{
	auto it = m_scenes.find(id);
	if (it == m_scenes.end()) {
		spdlog::error("There is no scene '{}'!", id);
		return;
	}

	Scene* newScene = it->second.get();
	if (m_pCurrentScene != newScene) {
		if (m_pCurrentScene) {
			m_pCurrentScene->onExit();
			m_pCurrentScene->resetWorld(Scene::AccessKey{});
		}

		m_pCurrentScene = newScene;
		
		m_pCurrentScene->getWorld().addSystem<AnimationSystem>(SystemPhase::Update);
		m_pCurrentScene->getWorld().addSystem<CameraSystem>(SystemPhase::Update);
		m_pCurrentScene->getWorld().addSystem<RenderSystem>(SystemPhase::Render);

		CameraEntity::create(m_pCurrentScene->getWorld());
		m_pCurrentScene->onEnter();
	}
}

void SceneManager::updateActiveScene()
{
	m_pCurrentScene->onUpdate();
	m_pCurrentScene->getWorld().update();
}

void SceneManager::renderActiveScene()
{
	m_pCurrentScene->onRender();
	m_pCurrentScene->getWorld().render();
}