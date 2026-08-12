#ifndef WORLD_HPP
#define WORLD_HPP

#include <entt/entt.hpp>

#include "entity.hpp"

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

private:
	entt::registry m_registry;
};

#endif