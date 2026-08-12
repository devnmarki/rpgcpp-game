#include "render_system.hpp"
#include "ecs/world.hpp"

RenderSystem::RenderSystem(World* world)
	: System(world)
{

}

void RenderSystem::tick(float dt)
{
	getWorld()->query<TransformComponent>([](auto entity, TransformComponent& t) {
		spdlog::info("X: {}, Y: {}", t.position.x, t.position.y);
	});
}