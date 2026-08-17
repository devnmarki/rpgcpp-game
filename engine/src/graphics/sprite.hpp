#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <optional>
#include <string>

#include <SDL3/SDL.h>
#include <nlohmann/json.hpp>

#include "loader/asset.hpp"

struct SpriteData {
	std::string id;
	std::string textureId = "";
	std::optional<SDL_FRect> src = std::nullopt;
	bool flipX = false;
	bool flipY = false;
};

struct SpriteConfig {
	SpriteData data;

	static SpriteConfig fromJson(const nlohmann::json& j) {
		SpriteConfig config;
		if (j.contains("texture_id")) {
			config.data.textureId = j["texture_id"];
		}
		if (j.contains("src") && j["src"].is_array() && j["src"].size() == 4) {
			config.data.src = SDL_FRect{
				.x = j["src"][0].get<float>(),
				.y = j["src"][1].get<float>(),
				.w = j["src"][2].get<float>(),
				.h = j["src"][3].get<float>()
			};
		}
		if (j.contains("flip_x")) {
			config.data.flipX = j["flip_x"];
		}
		if (j.contains("flip_y")) {
			config.data.flipY = j["flip_y"];
		}
		return config;
	}
};

class Sprite : public Asset {
public:
	Sprite() = default;
	Sprite(const SpriteData& data) : m_data(data) { }
	explicit Sprite(const SpriteConfig& config) : m_data(config.data) { }

	static SpriteConfig parseJson(const nlohmann::json& json) {
		return SpriteConfig::fromJson(json);
	}

	const std::string& getId() const { return m_data.id; }
	const std::string& getTextureId() const { return m_data.textureId; }
	std::optional<SDL_FRect> getSource() const { return m_data.src; }
	bool isFlipX() const { return m_data.flipX; }
	bool isFlipY() const { return m_data.flipY; }

private:
	SpriteData m_data;
};

#endif