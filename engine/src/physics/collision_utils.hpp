#ifndef COLLISIONUTILS_HPP
#define COLLISIONUTILS_HPP

#include "physics/collision_events.hpp"

template<typename Tag>
inline void onCollisionEnter(auto&& fn) {
	for (const auto& event : g_collisionEvents) {
		if (event.isTrigger || event.type != CollisionType::Enter)
			continue;

		if (!event.self.hasComponent<Tag>())
			continue;

		fn(event.self, event.other);
	}
}

template<typename Tag>
inline void onCollisionStay(auto&& fn) {
	for (const auto& event : g_collisionEvents) {
		if (event.isTrigger || event.type != CollisionType::Stay)
			continue;

		if (!event.self.hasComponent<Tag>())
			continue;

		fn(event.self, event.other);
	}
}

template<typename Tag>
inline void onCollisionExit(auto&& fn) {
	for (const auto& event : g_collisionEvents) {
		if (event.isTrigger || event.type != CollisionType::Exit)
			continue;

		if (!event.self.hasComponent<Tag>())
			continue;

		fn(event.self, event.other);
	}
}

template<typename Tag>
inline void onTriggerEnter(auto&& fn) {
	for (const auto& event : g_collisionEvents) {
		if (!event.isTrigger || event.type != CollisionType::Enter)
			continue;

		if (!event.self.hasComponent<Tag>())
			continue;

		fn(event.self, event.other);
	}
}

template<typename Tag>
inline void onTriggerStay(auto&& fn) {
	for (const auto& event : g_collisionEvents) {
		if (!event.isTrigger || event.type != CollisionType::Stay)
			continue;

		if (!event.self.hasComponent<Tag>())
			continue;

		fn(event.self, event.other);
	}
}

template<typename Tag>
inline void onTriggerExit(auto&& fn) {
	for (const auto& event : g_collisionEvents) {
		if (!event.isTrigger || event.type != CollisionType::Exit)
			continue;

		if (!event.self.hasComponent<Tag>())
			continue;

		fn(event.self, event.other);
	}
}

#endif