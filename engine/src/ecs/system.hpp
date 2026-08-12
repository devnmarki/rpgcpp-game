#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <entt/entt.hpp>

#include "components.hpp"

class World;

enum class SystemPhase {
	Update = 0,
	Render
};

class System {
public:
	System(World* world, SystemPhase phase = SystemPhase::Update) 
		: m_pWorld(world), m_phase(phase) { }
	virtual ~System() = default;

	virtual void tick(float dt) = 0;

	SystemPhase getPhase() const { return m_phase; }
	World* getWorld();

private:
	World* m_pWorld;
	SystemPhase m_phase;
};

#endif