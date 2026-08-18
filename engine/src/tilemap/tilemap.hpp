#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Tileset.hpp>

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

	const TilemapData& getData() const { return m_data; }
	tmx::Map& getMap() { return m_map; }
	const tmx::Map& getMap() const { return m_map; }

private:
	TilemapData m_data;
	tmx::Map m_map;
};

#endif