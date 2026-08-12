#include "world.hpp"
#include "core/app.hpp"

void World::update()
{
	for (const auto& system : m_systems) {
		if (system->getPhase() == SystemPhase::Update) {
			system->tick(App::getInstance().getTime().getDeltaTime());
		}
	}
}

void World::render()
{
	for (const auto& system : m_systems) {
		if (system->getPhase() == SystemPhase::Render) {
			system->tick(App::getInstance().getTime().getDeltaTime());
		}
	}
}

void World::clearEntities()
{
	m_registry.clear();
}