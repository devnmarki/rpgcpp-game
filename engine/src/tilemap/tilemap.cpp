#include "tilemap.hpp"

TilemapConfig TilemapConfig::fromJson(const nlohmann::json& json)
{
	TilemapConfig config;
	config.data.path = json.get<std::string>();
	return config;
}

Tilemap::Tilemap(const TilemapConfig& config)
	: m_data(config.data)
{
	if (!m_map.load(m_data.path)) {
		spdlog::info("Failed to load map: {}", m_data.path);
		return;
	}
}

TilemapConfig Tilemap::parseJson(const nlohmann::json& json)
{
	return TilemapConfig::fromJson(json);
}
