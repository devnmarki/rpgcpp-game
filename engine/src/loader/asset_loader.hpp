#ifndef ASSETLOADER_HPP
#define ASSETLOADER_HPP

#include <string>
#include <unordered_map>
#include <fstream>

#include <nlohmann/json.hpp>

#include "graphics/texture.hpp"
#include "graphics/sprite.hpp"

class AssetLoader {
public:
	AssetLoader() = default;

	template<typename T>
	void load(const std::string& id, const typename AssetTraits<T>::ConfigType& config) {
		auto asset = std::make_shared<T>(config);

		auto [it, success] = m_assets.insert({ id, asset });
		if (!success) {
			spdlog::error("Asset '{}' already exists!", id);
			return;
		}
		spdlog::info("Loaded asset '{}' successfully!", id);
	}

	template<typename T>
	void loadGroup(const std::string& filename) {
		std::ifstream file(filename);
		if (!file.is_open()) {
			spdlog::error("Failed to load file: '{}'!", filename);
			return;
		}

		nlohmann::json data;
		file >> data;

		for (const auto& [id, jsonValue] : data.items()) {
			load<T>(id, T::parseJson(jsonValue));
		}
	}

	template<typename T>
	T* get(const std::string& id) {
		auto it = m_assets.find(id);
		if (it != m_assets.end()) {
			auto derived = std::dynamic_pointer_cast<T>(it->second);
			return derived ? derived.get() : nullptr;
		}
		return nullptr;
	}

private:
	std::unordered_map<std::string, std::shared_ptr<Asset>> m_assets;
};

#endif