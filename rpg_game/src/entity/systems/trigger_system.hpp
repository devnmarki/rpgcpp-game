#ifndef TRIGGERSYSTEM_HPP
#define TRIGGERSYSTEM_HPP

#include "core/engine.hpp"
#include "components.hpp"
#include "gconstants.hpp"

class TriggerSystem : public System {
public:
	TriggerSystem(World* world, SystemPhase phase = SystemPhase::Update);

	void tick(float dt) override;
};

#endif