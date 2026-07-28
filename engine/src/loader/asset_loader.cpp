#include "asset_loader.hpp"

bool AssetLoader::loadTexture(const std::string& id, const std::string& path)
{
	std::shared_ptr<Texture> texture = std::make_shared<Texture>(path);

	auto [it, success] = m_textures.insert({ id, texture });
	if (!success) {
		spdlog::error("Failed to load texture '{}'!", id);
		return false;
	}
	spdlog::info("Loaded texture '{}' successfully!", id);
	return true;
}

void AssetLoader::loadTextureGroup(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open()) {
		spdlog::error("Failed to load file: '{}'!", filename);
		return;
	}

	nlohmann::json data;
	file >> data;

	for (const auto& [id, path] : data.items()) {
		if (!path.is_string())
			continue;

		loadTexture(id, path);
	}
}

Texture* AssetLoader::getTexture(const std::string& id) const
{
	auto it = m_textures.find(id);
	if (it != m_textures.end())
		return it->second.get();

	return nullptr;
}
