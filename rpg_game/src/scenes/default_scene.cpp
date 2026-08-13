#include "default_scene.hpp"

void DefaultScene::onEnter()
{
	spdlog::info("Default Scene started!");

	//Entity entity = getWorld().createEntity();
	//auto& t = entity.addComponent<TransformComponent>();
	//t.position = glm::vec2(100.0f, 350.0f);
	//t.scale = glm::vec2(4.0f, 4.0f);
	//auto& sr = entity.addComponent<SpriteRendererComponent>();
	//sr.spriteId = "sprite:character_base_down";

	//Entity entity2 = getWorld().createEntity();
	//auto& t2 = entity2.addComponent<TransformComponent>();
	//t2.position = glm::vec2(350.0f, 200.0f);
	//t2.scale = glm::vec2(4.0f, 4.0f);
	//t2.rotation = 45.0f;
	//auto& sr2 = entity2.addComponent<SpriteRendererComponent>();
	//sr2.spriteId = "sprite:character_base_left";

	EntityTemplates::createPlayer(getWorld(), glm::vec2(400.0f, 350.0f));
}