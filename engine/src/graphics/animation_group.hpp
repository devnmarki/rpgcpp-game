#ifndef ANIMATIONGROUP_HPP
#define ANIMATIONGROUP_HPP

#include <vector>
#include <string>
#include <unordered_map>

#include <nlohmann/json.hpp>

#include "loader/asset.hpp"
#include "animation.hpp"

struct AnimationGroupData {
	std::string id = "";
	std::unordered_map<std::string, AnimationData> animations;
};

struct AnimationGroupConfig {
	AnimationGroupData data;

	static AnimationGroupConfig fromJson(const nlohmann::json& json);
};

class AnimationGroup : public Asset {
public:
	AnimationGroup() = default;
	explicit AnimationGroup(const AnimationGroupConfig& config);

	static AnimationGroupConfig parseJson(const nlohmann::json& json);

	AnimationGroupData& getData() { return m_data; }
	const AnimationGroupData& getData() const { return m_data; } 

private:
	AnimationGroupData m_data;
};

#endif