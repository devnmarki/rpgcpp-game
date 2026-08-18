#include "render_system.hpp"
#include "ecs/world.hpp"
#include "core/app.hpp"

RenderSystem::RenderSystem(World* world, SystemPhase phase)
	: System(world, phase)
{

}

void RenderSystem::tick(float dt)
{
	renderTilemaps();
	renderSprites();
}

void RenderSystem::renderSprites()
{
	getWorld()->query<TransformComponent, SpriteRendererComponent>([&](Entity entity, TransformComponent& t, SpriteRendererComponent& sr) {
		Sprite* sprite = App::getInstance().getAssetLoader().get<Sprite>(sr.spriteId);
		if (!sprite)
			return;

		App::getInstance().getRenderer().drawSprite(sprite, t);
	});
}

void RenderSystem::renderTilemaps()
{
    const float screenW = static_cast<float>(App::getInstance().getWindow().getWidth());
    const float screenH = static_cast<float>(App::getInstance().getWindow().getHeight());
    const int marginTiles = 2;

    getWorld()->query<TransformComponent, TilemapComponent>(
        [&](Entity, TransformComponent& transform, TilemapComponent& tilemapComp)
        {
            Tilemap* tilemapAsset = App::getInstance().getAssetLoader().get<Tilemap>(tilemapComp.tilemapId);
            if (!tilemapAsset) return;

            const tmx::Map& map = tilemapAsset->getMap();
            const auto tileSize = map.getTileSize();
            const auto mapSize = map.getTileCount();

            const float tileW = static_cast<float>(tileSize.x) * transform.scale.x;
            const float tileH = static_cast<float>(tileSize.y) * transform.scale.y;
            const glm::vec2 mapOrigin = transform.position;

            int startX = static_cast<int>(std::floor((0.0f - mapOrigin.x) / tileW)) - marginTiles;
            int startY = static_cast<int>(std::floor((0.0f - mapOrigin.y) / tileH)) - marginTiles;
            int endX = static_cast<int>(std::ceil((screenW - mapOrigin.x) / tileW)) + marginTiles;
            int endY = static_cast<int>(std::ceil((screenH - mapOrigin.y) / tileH)) + marginTiles;

            startX = std::max(0, startX);
            startY = std::max(0, startY);
            endX = std::min(static_cast<int>(mapSize.x), endX);
            endY = std::min(static_cast<int>(mapSize.y), endY);

            if (startX >= endX || startY >= endY)
                return;

            for (const auto& layerPtr : map.getLayers())
            {
                if (layerPtr->getType() != tmx::Layer::Type::Tile)
                    continue;

                const auto& tileLayer = layerPtr->getLayerAs<tmx::TileLayer>();
                const auto& tiles = tileLayer.getTiles();
                if (tiles.empty()) continue;

                for (int ty = startY; ty < endY; ++ty)
                {
                    for (int tx = startX; tx < endX; ++tx)
                    {
                        const size_t index = static_cast<size_t>(ty * mapSize.x + tx);
                        if (index >= tiles.size()) continue;

                        const auto& tile = tiles[index];
                        if (tile.ID == 0) continue;

                        const tmx::Tileset* tileset = findTileset(map, tile.ID);
                        if (!tileset) continue;

                        const uint32_t localId = tile.ID - tileset->getFirstGID();

                        std::string textureId = "texture:" + tileset->getName();
                        Texture* tex = App::getInstance().getAssetLoader().get<Texture>(textureId);
                        if (!tex) continue;

                        const auto tsTileSize = tileset->getTileSize();
                        const uint32_t columns = tileset->getColumnCount() > 0
                            ? tileset->getColumnCount()
                            : (tileset->getImageSize().x / tsTileSize.x);

                        const uint32_t tu = localId % columns;
                        const uint32_t tv = localId / columns;

                        SDL_FRect src{
                            static_cast<float>(tu * tsTileSize.x + tileset->getMargin() + tu * tileset->getSpacing()),
                            static_cast<float>(tv * tsTileSize.y + tileset->getMargin() + tv * tileset->getSpacing()),
                            static_cast<float>(tsTileSize.x),
                            static_cast<float>(tsTileSize.y)
                        };

                        glm::vec2 pos{
                            mapOrigin.x + tx * tileW,
                            mapOrigin.y + ty * tileH
                        };

                        SDL_FRect dst{
                            pos.x,
                            pos.y,
                            tileW,
                            tileH
                        };

                        SDL_FlipMode flip = SDL_FLIP_NONE;
                        if (tile.flipFlags & tmx::TileLayer::FlipFlag::Horizontal)
                            flip = static_cast<SDL_FlipMode>(flip | SDL_FLIP_HORIZONTAL);
                        if (tile.flipFlags & tmx::TileLayer::FlipFlag::Vertical)
                            flip = static_cast<SDL_FlipMode>(flip | SDL_FLIP_VERTICAL);

                        SDL_RenderTextureRotated(
                            App::getInstance().getRenderer().getHandle(),
                            tex->getHandle(),
                            &src,
                            &dst,
                            0.0f,
                            nullptr,
                            flip
                        );
                    }
                }
            }
        });
}

const tmx::Tileset* RenderSystem::findTileset(const tmx::Map& map, uint32_t gid)
{
	if (gid == 0)
		return nullptr;

	const auto& tilesets = map.getTilesets();
	for (auto it = tilesets.rbegin(); it != tilesets.rend(); ++it) {
		if (gid >= it->getFirstGID() && gid <= it->getLastGID()) {
			return &(*it);
		}
	}

	return nullptr;
}