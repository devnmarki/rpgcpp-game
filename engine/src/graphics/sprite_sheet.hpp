#ifndef SPRITESHEET_HPP
#define SPRITESHEET_HPP

#include <vector>

#include <glm/glm.hpp>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>

#include "loader/asset.hpp"
#include "sprite.hpp"

struct SpriteSheetData {
	std::string id;
	std::string textureId = "";
	int rows = 0;
	int columns = 0;
	glm::vec2 spriteSize = glm::vec2(0.0f);
	bool flipX = false;
	bool flipY = false;
};

struct SpriteSheetConfig {
	SpriteSheetData data;

	static SpriteSheetConfig fromJson(const nlohmann::json& json) {
		SpriteSheetConfig config;

		if (json.contains("texture_id")) {
			config.data.textureId = json["texture_id"];
		}

		if (json.contains("rows")) {
			config.data.rows = json["rows"];
		}
		if (json.contains("columns")) {
			config.data.columns = json["columns"];
		}

		if (json.contains("sprite_size") && json["sprite_size"].is_array() && json["sprite_size"].size() == 2) {
			config.data.spriteSize.x = json["sprite_size"][0];
			config.data.spriteSize.y = json["sprite_size"][1];
		}

		if (json.contains("flip_x")) {
			config.data.flipX = json["flip_x"];
		}
		if (json.contains("flip_y")) {
			config.data.flipY = json["flip_y"];
		}

		return config;
	}
};

class SpriteSheet : public Asset {
public:
	SpriteSheet() = default;
	explicit SpriteSheet(const SpriteSheetConfig& config);

	static SpriteSheetConfig parseJson(const nlohmann::json& json) {
		return SpriteSheetConfig::fromJson(json);
	}

	Sprite* getSprite(int index);
	std::string getSpriteId(int index);

private:
	void generateSprites();

private:
	SpriteSheetData m_data;

	std::vector<Sprite> m_sprites;
};

#endif