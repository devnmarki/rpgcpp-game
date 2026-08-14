#ifndef WORLD_HPP
#define WORLD_HPP

#include <entt/entt.hpp>

#include "entity.hpp"
#include "utils/time.hpp"
#include "system.hpp"

class World {
public:
	World() = default;

	Entity createEntity() {
		entt::entity eid = m_registry.create();
		return Entity(eid, &m_registry);
	}

	template<typename T, typename... Args>
	T& emplace(entt::entity eid, Args&&... args) {
		return m_registry.emplace<T>(eid, std::forward<Args>(args)...);
	}

	template<typename T>
	T& get(entt::entity eid) {
		return m_registry.get<T>(eid);
	}

	template<typename T>
	bool has(entt::entity eid) {
		return m_registry.any_of<T>(eid);
	}

	template<typename T, typename... Args>
	void addSystem(SystemPhase phase = SystemPhase::Update, Args&&... args) {
		m_systems.emplace_back(std::make_unique<T>(this, phase, std::forward<Args>(args)...));
	}

	void update();
	void render();

	template<typename... Components, typename Func>
	void query(Func&& func) {
		auto view = m_registry.view<Components...>();
		view.each([this, &func](auto eid, Components&... comps) {
			Entity entity(eid, &m_registry);
			func(entity, comps...);
		}); 
	}

	void clearEntities();

	std::vector<std::unique_ptr<System>>& getSystems() { return m_systems; }

private:
	entt::registry m_registry;

	std::vector<std::unique_ptr<System>> m_systems;
};

#endif