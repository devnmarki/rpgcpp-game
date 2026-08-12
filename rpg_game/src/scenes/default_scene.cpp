#include "default_scene.hpp"

void DefaultScene::onEnter()
{
	spdlog::info("Default Scene started!");

	m_pSprite = std::make_shared<Sprite>(Sprite{ .textureId = "character_base_sheet" });

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
		getRenderer().drawSprite(m_pSprite.get(), t);
	});
}