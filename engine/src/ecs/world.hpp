#ifndef WORLD_HPP
#define WORLD_HPP

#include <tuple>
#include <type_traits>

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
		for (auto eid : view) {
			Entity entity(eid, &m_registry);
			auto args = std::tuple_cat(queryArg<Components>(view, eid)...);
			std::apply([&](auto&... comps) { func(entity, comps...); }, args);
		}
	}

	void clearEntities();

	std::vector<std::unique_ptr<System>>& getSystems() { return m_systems; }
	entt::registry& getRegistry() { return m_registry; }

private:
	template<typename Component, typename View>
	static auto queryArg(View& view, entt::entity eid) {
		if constexpr (std::is_empty_v<Component>) {
			return std::tuple<>{};
		}
		else {
			return std::tuple<Component&>(view.template get<Component>(eid));
		}
	}

private:
	entt::registry m_registry;

	std::vector<std::unique_ptr<System>> m_systems;
};

#endif