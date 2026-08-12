#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <entt/entt.hpp>

#include "core_components.hpp"

class World;

class System {
public:
	System(World* world) 
		: m_pWorld(world) { }

	virtual void tick(float dt) { }

	World* getWorld();

private:
	World* m_pWorld;
};

#endif