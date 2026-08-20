#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <string>
#include <memory>
#include <unordered_map>

#include <spdlog/spdlog.h>

#include "scene.hpp"
#include "graphics/render_system.hpp"
#include "graphics/animation_system.hpp"
#include "camera_system.hpp"
#include "physics/physics_system.hpp"
#include "camera_entity.hpp"

class SceneManager {
public:
	SceneManager() = default;

	template<typename T>
	void addScene(const std::string& id) {
		std::unique_ptr<T> scene = std::make_unique<T>();

		auto [it, success] = m_scenes.insert({ id, std::move(scene) });
		if (!success) {
			spdlog::error("Failed to add scene '{}'!", id);
			return;
		}
		spdlog::info("Successfully added scene '{}'!", id);
	}

	void switchScene(const std::string& id);

	void updateActiveScene();
	void renderActiveScene();

	Scene* getActiveScene() const { return m_pCurrentScene; }

private:
	void initSystems();

private:
	std::unordered_map<std::string, std::unique_ptr<Scene>> m_scenes = {};
	Scene* m_pCurrentScene = nullptr;
};

#endif