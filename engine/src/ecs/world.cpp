#include "world.hpp"
#include "core/app.hpp"

void World::update()
{
	auto& systems = m_systems.at(SystemPhase::Update);
	for (const auto& system : systems) {
		system->tick(App::getInstance().getTime().getDeltaTime());
	}
}

void World::render()
{
	auto& systems = m_systems.at(SystemPhase::Render);
	for (const auto& system : systems) {
		system->tick(App::getInstance().getTime().getDeltaTime());
	}
}

void World::clearEntities()
{
	m_registry.clear();
}