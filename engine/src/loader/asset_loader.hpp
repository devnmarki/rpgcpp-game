#ifndef ASSETLOADER_HPP
#define ASSETLOADER_HPP

#include <string>
#include <unordered_map>
#include <fstream>

#include <nlohmann/json.hpp>

#include "graphics/texture.hpp"

class AssetLoader {
public:
	AssetLoader() = default;

	bool loadTexture(const std::string& id, const std::string& path);
	void loadTextureGroup(const std::string& filename);

	Texture* getTexture(const std::string& id) const;

private:
	std::unordered_map<std::string, std::shared_ptr<Texture>> m_textures = {};
};

#endif