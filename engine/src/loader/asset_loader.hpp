#ifndef ASSETLOADER_HPP
#define ASSETLOADER_HPP

#include <string>
#include <unordered_map>

#include "graphics/texture.hpp"

class AssetLoader {
public:
	AssetLoader() = default;

	void loadTexture(const std::string& id, const std::string& path);

	Texture* getTexture(const std::string& id) const;

private:
	std::unordered_map<std::string, std::shared_ptr<Texture>> m_textures = {};
};

#endif