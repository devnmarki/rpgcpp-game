#include "island_scene.hpp"

void IslandScene::onEnter()
{
	spdlog::info("Entered island scene!");
}

void IslandScene::onRender()
{
	getRenderer().drawRect(glm::vec2(100.f, 250.f), glm::vec2(100.f, 50.f), { 255, 0, 0 });
	getRenderer().fillRect(glm::vec2(100.f, 350.f), glm::vec2(100.f, 50.f), { 0, 255, 0 });
}
