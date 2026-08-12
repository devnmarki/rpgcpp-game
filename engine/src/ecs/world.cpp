#include "world.hpp"
#include "core/app.hpp"

void World::update()
{
	for (const auto& system : m_systems) {
		system->tick(App::getInstance().getTime().getDeltaTime());
	}
}

void World::clearEntities()
{
	m_registry.clear();
}