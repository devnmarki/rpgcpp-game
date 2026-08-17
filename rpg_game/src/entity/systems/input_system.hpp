#ifndef INPUTSYSTEM_HPP
#define INPUTSYSTEM_HPP

#include "core/engine.hpp"

#include "components.hpp"

class InputSystem : public System {
public:
	InputSystem(World* world, SystemPhase phase = SystemPhase::Update);

	void tick(float dt) override;
};

#endif