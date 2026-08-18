#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <nlohmann/json.hpp>
#include <tmxlite/Map.hpp>

#include "loader/asset.hpp"

struct TilemapData {
	std::string id = "";
	std::string path;
};

struct TilemapConfig {
	TilemapData data;

	static TilemapConfig fromJson(const nlohmann::json& json);
};

class Tilemap : public Asset {
public:
	Tilemap() = default;
	explicit Tilemap(const TilemapConfig& config);

	static TilemapConfig parseJson(const nlohmann::json& json);

private:
	TilemapData m_data;
};

#endif