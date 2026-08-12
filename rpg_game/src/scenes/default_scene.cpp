#include "default_scene.hpp"

void DefaultScene::onEnter()
{
	spdlog::info("Default Scene started!");

	Entity entity = getWorld().createEntity();
	auto& t = entity.addComponent<TransformComponent>();
	t.position = glm::vec2(100.0f, 200.0f);

	getWorld().query<TransformComponent>([](entt::entity eid, TransformComponent& t) {
		spdlog::info("X: {}, Y: {}", t.position.x, t.position.y);
	});
}

void DefaultScene::onRender()
{
	SDL_FRect src = { 0, 0, 32, 32 };
	static float x = 100.0f;
	x += 1.0f;
	getRenderer().drawTexture(getAssetLoader().getTexture("character_base_sheet"), { x, 100 }, &src, { 4, 4 });
}