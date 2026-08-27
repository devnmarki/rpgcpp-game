#include "tilemap_system.hpp"
#include "ecs/world.hpp"
#include "core/app.hpp"
#include "prefab/prefab_factory.hpp"

TilemapSystem::TilemapSystem(World* world, SystemPhase phase)
	: System(world, phase)
{

}

void TilemapSystem::tick(float dt)
{
	loadColliders();
	loadEntities();
}

void TilemapSystem::loadColliders()
{
	getWorld()->query<TilemapComponent, TilemapColliderComponent, TransformComponent>
		([this](Entity, TilemapComponent& tilemap, TilemapColliderComponent& collider, TransformComponent& transform) {
		if (collider.initialized || collider.layerId.empty())
			return;

		for (const auto& object : getObjects(tilemap, collider.layerId)) {
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

		collider.initialized = true;
	});
}

void TilemapSystem::loadEntities()
{
	getWorld()->query<TilemapComponent, TilemapSpawnerComponent, TransformComponent>
		([this](Entity, TilemapComponent& tilemap, TilemapSpawnerComponent& spawner, TransformComponent& transform) {
		if (spawner.initialized || spawner.layerId.empty())
			return;

		for (const auto& object : getObjects(tilemap, spawner.layerId)) {
			glm::vec2 center = {
				object.getPosition().x * transform.scale.x,
				object.getPosition().y * transform.scale.y
			};

			center += transform.position;

			Entity entity = PrefabFactory::create(object.getName(), *getWorld(), center);
		}

		spawner.initialized = true;
	});
}

std::vector<tmx::Object> TilemapSystem::getObjects(TilemapComponent& tilemap, const std::string& layerId)
{
	std::vector<tmx::Object> objectsList;

	Tilemap* tilemapAsset = App::getInstance().getAssetLoader().get<Tilemap>(tilemap.tilemapId);
	if (!tilemapAsset)
		return objectsList;

	for (const auto& layerPtr : tilemapAsset->getMap().getLayers()) {
		if (layerPtr->getType() != tmx::Layer::Type::Object)
			continue;

		const auto& objectsLayer = layerPtr->getLayerAs<tmx::ObjectGroup>();

		if (objectsLayer.getName() == layerId) {
			for (const auto& object : objectsLayer.getObjects()) {
				objectsList.push_back(object);
			}
		}
	}

	return objectsList;
}