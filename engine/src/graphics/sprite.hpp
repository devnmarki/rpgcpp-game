#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <optional>
#include <string>

#include <SDL3/SDL.h>
#include <nlohmann/json.hpp>

#include "loader/asset.hpp"

struct SpriteConfig {
	std::string textureId = "";
	std::optional<SDL_FRect> src = std::nullopt;
	bool flipX = false;
	bool flipY = false;

	static SpriteConfig fromJson(const nlohmann::json& j) {
		SpriteConfig config;
		if (j.contains("texture_id")) {
			config.textureId = j["texture_id"];
		}
		if (j.contains("src") && j["src"].is_array() && j["src"].size() == 4) {
			config.src = SDL_FRect{
				.x = j["src"][0].get<float>(),
				.y = j["src"][1].get<float>(),
				.w = j["src"][2].get<float>(),
				.h = j["src"][3].get<float>()
			};
		}
		if (j.contains("flip_x")) {
			config.flipX = j["flip_x"];
		}
		if (j.contains("flip_y")) {
			config.flipY = j["flip_y"];
		}
		return config;
	}
};

struct Sprite : public Asset {
	std::string textureId = "";
	std::optional<SDL_FRect> src = std::nullopt;
	bool flipX = false;
	bool flipY = false;

	Sprite() = default;
	explicit Sprite(const SpriteConfig& config)
		: textureId(config.textureId), src(config.src), flipX(config.flipX), flipY(config.flipY) { }

	static SpriteConfig parseJson(const nlohmann::json& json) {
		return SpriteConfig::fromJson(json);
	}
};

#endif