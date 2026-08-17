#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <iostream>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>

#include "loader/asset.hpp"

struct TextureData {
	std::string id;
	std::string path;
};

struct TextureConfig {
	TextureData data;

	static TextureConfig fromJson(const nlohmann::json& json) {
		TextureConfig config;
		config.data.path = json.get<std::string>();

		return config;
	}
};

class Texture : public Asset {
public:
	Texture(const TextureData& data);
	explicit Texture(const TextureConfig& config);
	~Texture();

	static TextureConfig parseJson(const nlohmann::json& json) {
		return TextureConfig::fromJson(json);
	}

	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	SDL_Texture* getHandle() const { return m_pHandle; }

private:
	TextureData m_data;
	float m_width = 0.0f;
	float m_height = 0.0f;
	SDL_Texture* m_pHandle;
};

#endif