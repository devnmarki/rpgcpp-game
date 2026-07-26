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
		}

		m_pCurrentScene = newScene;
		m_pCurrentScene->onEnter();
	}
}