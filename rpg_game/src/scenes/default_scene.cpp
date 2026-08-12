#include "default_scene.hpp"

void DefaultScene::onEnter()
{
	spdlog::info("Default Scene started!");

	Entity entity = getWorld().createEntity();
	auto& t = entity.addComponent<TransformComponent>();
	t.position = glm::vec2(100.0f, 350.0f);
	t.scale = glm::vec2(4.0f, 4.0f);
}

void DefaultScene::onRender()
{
	getWorld().query<TransformComponent>([&](entt::entity eid, TransformComponent& t) {
		t.rotation += 1.0f;
		t.position.x += 1.0f;
		getRenderer().drawSprite(getAssetLoader().get<Sprite>("sprite:character_base_down"), t);
	});
}