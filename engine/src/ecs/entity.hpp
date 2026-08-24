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
	void addComponent(Args&&... args) {
		m_registry->emplace_or_replace<T>(m_eid, std::forward<Args>(args)...);
	}

	template<typename T, typename... Args>
	T& getOrAddComponent(Args&&... args)
	{
		if (hasComponent<T>())
			return getComponent<T>();

		addComponent<T>(std::forward<Args>(args)...);
		return getComponent<T>();
	}

	template<typename T>
	T& getComponent() {
		return m_registry->get<T>(m_eid);
	}

	template<typename T>
	const T& getComponent() const {
		return m_registry->get<T>(m_eid);
	}

	template<typename T>
	bool hasComponent() const {
		return m_registry->any_of<T>(m_eid);
	}

	template<typename T>
	void removeComponent() {
		m_registry->remove<T>(m_eid);
	}

	void destroy() {
		m_registry->destroy(m_eid);
		m_eid = entt::null;
		m_registry = nullptr;
	}

	bool isValid() const {
		return m_registry != nullptr && m_eid != entt::null && m_registry->valid(m_eid);
	}

	entt::entity getId() const { return m_eid; }

	bool operator==(const Entity& other) const {
		return m_eid == other.getId();
	}

	bool operator!=(const Entity& other) const {
		return !(*this == other);
	}

private:
	entt::entity m_eid{entt::null};
	entt::registry* m_registry{nullptr};
};

#endif