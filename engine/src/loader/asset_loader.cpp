#include "asset_loader.hpp"

void AssetLoader::loadTexture(const std::string& id, const std::string& path)
{
	std::shared_ptr<Texture> texture = std::make_shared<Texture>(path);

	auto [it, success] = m_textures.insert({ id, texture });
	if (!success) {
		spdlog::error("Failed to load texture '{}'!", id);
		return;
	}
	spdlog::info("Loaded texture '{}' successfully!", id);
}

Texture* AssetLoader::getTexture(const std::string& id) const
{
	auto it = m_textures.find(id);
	if (it != m_textures.end())
		return it->second.get();

	return nullptr;
}
