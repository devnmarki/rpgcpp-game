#include "physics_system.hpp"
#include "ecs/world.hpp"
#include "core/app.hpp"

PhysicsSystem::PhysicsSystem(World* world, SystemPhase phase)
	: System(world, phase)
{

}

void PhysicsSystem::tick(float dt)
{
	float timeStep = 1.0f / 60.0f;
	int subStepCount = 4;
	Scene* activeScene = App::getInstance().getSceneManager().getActiveScene();
	
	for (int frame = 0; frame < 60; ++frame) {
		b2World_Step(activeScene->getPhysicsWorldId(), timeStep, subStepCount);
	}
}