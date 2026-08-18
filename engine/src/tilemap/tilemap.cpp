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

}

TilemapConfig Tilemap::parseJson(const nlohmann::json& json)
{
	return TilemapConfig::fromJson(json);
}
