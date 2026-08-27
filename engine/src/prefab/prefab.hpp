#ifndef PREFAB_HPP
#define PREFAB_HPP

#include "ecs/world.hpp"

class Prefab {
public:
	virtual ~Prefab() = default;

	virtual Entity build(World& world, const glm::vec2& position) const = 0;
};

#endif