#ifndef COLLISIONEVENTS_HPP
#define COLLISIONEVENTS_HPP

#include <vector>

#include <glm/glm.hpp>

#include "ecs/entity.hpp"

enum class CollisionType {
	Enter,
	Stay,
	Exit
};

struct CollisionEvent {
	CollisionType type;
	Entity self;
	Entity other;
	bool isTrigger = false;

	glm::vec2 normal = { 0.f, 0.f };
	glm::vec2 point  = { 0.f, 0.f };
};

inline std::vector<CollisionEvent> g_collisionEvents;

#endif