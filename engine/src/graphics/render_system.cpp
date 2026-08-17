#include "render_system.hpp"
#include "ecs/world.hpp"
#include "core/app.hpp"

RenderSystem::RenderSystem(World* world, SystemPhase phase)
	: System(world, phase)
{

}

void RenderSystem::tick(float dt)
{
	getWorld()->query<TransformComponent, SpriteRendererComponent>([&](Entity entity, TransformComponent& t, SpriteRendererComponent& sr) {
		Sprite* sprite = App::getInstance().getAssetLoader().get<Sprite>(sr.spriteId);
		if (!sprite)
			return;

		App::getInstance().getRenderer().drawSprite(sprite, t);
	});
}