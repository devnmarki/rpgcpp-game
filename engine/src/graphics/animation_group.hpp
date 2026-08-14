#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <vector>
#include <string>
#include <unordered_map>

#include <nlohmann/json.hpp>

#include "loader/asset.hpp"

struct AnimationData {
	std::string id = "";
	std::string spriteSheetId = "";
	std::vector<int> frames;
	float frameDuration = 0.1f;
	bool loop = true;
};

struct AnimationGroupData {
	std::string id = "";
	std::unordered_map<std::string, AnimationData> animations;
};

struct AnimationGroupConfig {
	AnimationGroupData data;

	static AnimationGroupConfig fromJson(const nlohmann::json& json) {
		AnimationGroupConfig config;

		if (json.contains("animations") && json["animations"].is_object()) {
			for (const auto& [animName, animJson] : json["animations"].items()) {
				AnimationData animData;

				if (animJson.contains("sprite_sheet_id")) {
					animData.spriteSheetId = animJson["sprite_sheet_id"];
				}
				if (animJson.contains("frames") && animJson["frames"].is_array()) {
					animData.frames = animJson["frames"].get<std::vector<int>>();
				}
				if (animJson.contains("frame_duration")) {
					animData.frameDuration = animJson["frame_duration"];
				}
				if (animJson.contains("loop")) {
					animData.loop = animJson["loop"];
				}

				config.data.animations[animName] = animData;
			}
		}

		return config;
	}
};

class AnimationGroup : public Asset {
public:
	AnimationGroup() = default;
	explicit AnimationGroup(const AnimationGroupConfig& config)
		: m_data(config.data) { }

	static AnimationGroupConfig parseJson(const nlohmann::json& json) {
		return AnimationGroupConfig::fromJson(json);
	}

private:
	AnimationGroupData m_data;
};

#endif