#ifndef PREFABFACTORY_HPP
#define PREFABFACTORY_HPP

#include <string>
#include <unordered_map>
#include <functional>

#include "prefab.hpp"

class PrefabFactory {
public:
	using CreatorFn = std::function<Entity(World&, const glm::vec2&)>;
	using Registry = std::unordered_map<std::string, CreatorFn>;
	
	template<typename PrefabT, typename ConfigFn = std::function<void(PrefabT&)>>
	static void add(const std::string& name, ConfigFn config = nullptr) {
		PrefabT prefab;
		
		if (config)
			config(prefab);
		
		getRegistry()[name] = [prefab](World& w, const glm::vec2& p) -> Entity {
			return prefab.build(w, p);
		};
	}

	static Entity create(const std::string& name, World& w, const glm::vec2& p) {
		auto& registry = getRegistry();
		auto it = registry.find(name);
		if (it != registry.end()) {
			return it->second(w, p);
		}
		return Entity{};
	}

private:
	static Registry& getRegistry() {
		static Registry registry;
		return registry;
	}
};

#endif