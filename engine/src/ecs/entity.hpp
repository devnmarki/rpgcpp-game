#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <entt/entt.hpp>

class Entity {
public:
	Entity() = default;
	Entity(entt::entity eid, entt::registry* registry)
		: m_eid(eid), m_registry(registry) { }

	virtual ~Entity() = default;

	template<typename T, typename... Args>
	T& addComponent(Args&&... args) {
		return m_registry->emplace<T>(m_eid, std::forward<Args>(args)...);
	}

	template<typename T>
	T& getComponent() {
		return m_registry->get<T>(m_eid);
	}

	template<typename T>
	bool hasComponent() {
		return m_registry->any_of<T>(m_eid);
	}

	template<typename T>
	T& removeComponent() {
		return m_registry->remove<T>(m_eid);
	}

	void destroy() {
		m_registry->destroy(m_eid);
		m_eid = entt::null;
		m_registry = nullptr;
	}

	entt::entity& getId() { return m_eid; }

private:
	entt::entity m_eid{entt::null};
	entt::registry* m_registry{nullptr};
};

#endif