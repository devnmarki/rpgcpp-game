#include "tilemap_system.hpp"
#include "ecs/world.hpp"
#include "core/app.hpp"


TilemapSystem::TilemapSystem(World* world, SystemPhase phase)
	: System(world, phase)
{

}

void TilemapSystem::tick(float dt)
{
	getWorld()->query<TilemapComponent, TransformComponent>
		([this](Entity, TilemapComponent& tilemap, TransformComponent& transform) {
		if (tilemap.collidersInitialized || tilemap.colliderLayerName.empty())
			return;

		Tilemap* tilemapAsset = App::getInstance().getAssetLoader().get<Tilemap>(tilemap.tilemapId);
		if (!tilemapAsset)
			return;

		for (const auto& layerPtr : tilemapAsset->getMap().getLayers()) {
			if (layerPtr->getType() != tmx::Layer::Type::Object)
				continue;

			const auto& objectsLayer = layerPtr->getLayerAs<tmx::ObjectGroup>();

			if (objectsLayer.getName() == tilemap.colliderLayerName) {
				const auto& objects = objectsLayer.getObjects();

				for (const auto& object : objects) {
					glm::vec2 size = {
						object.getAABB().width * transform.scale.x,
						object.getAABB().height * transform.scale.y
					};

					glm::vec2 center = {
						object.getPosition().x * transform.scale.x + size.x * 0.5f,
						object.getPosition().y * transform.scale.y + size.y * 0.5f
					};

					center += transform.position;

					Entity colliderEntity = getWorld()->createEntity();
					colliderEntity.addComponent<TransformComponent>(TransformComponent{
						.position = center,
						.scale = transform.scale
					});
					colliderEntity.addComponent<BoxColliderComponent>(BoxColliderComponent{
						.size = size
					});
				}
			}
		}

		tilemap.collidersInitialized = true;
	});
}
