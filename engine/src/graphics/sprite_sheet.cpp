#include "sprite_sheet.hpp"
#include "core/app.hpp"

SpriteSheet::SpriteSheet(const SpriteSheetConfig& config)
	: m_data(config.data)
{
	generateSprites();
}

Sprite* SpriteSheet::getSprite(int index)
{
	if (index > m_sprites.size() - 1 || index < 0)
		return nullptr;

	return &m_sprites[index];
}

std::string SpriteSheet::getSpriteId(int index)
{
	return getSprite(index)->getId();
}

void SpriteSheet::generateSprites()
{
	std::string sheetName = m_data.id;
	if (sheetName.rfind("sheet:", 0) == 0) {
		sheetName = sheetName.substr(6);
	}

	for (int i = 0; i < m_data.rows; i++) {
		for (int j = 0; j < m_data.columns; j++) {
			std::string spriteId = "sprite:" + sheetName + "_" + std::to_string(j) + "_" + std::to_string(i);
			SpriteData data = {
				.id = spriteId,
				.textureId = m_data.textureId,
				.src = SDL_FRect{
					.x = j * m_data.spriteSize.x,
					.y = i * m_data.spriteSize.y,
					.w = m_data.spriteSize.x,
					.h = m_data.spriteSize.y
				},
				.flipX = m_data.flipX,
				.flipY = m_data.flipY
			};
			Sprite newSprite(data);
			m_sprites.push_back(newSprite);
			App::getInstance().getAssetLoader().loadRaw(spriteId, std::make_shared<Sprite>(newSprite));
		}
	}
}