#include "animation_group.hpp"
#include "core/app.hpp"

AnimationGroup::AnimationGroup(const AnimationGroupConfig& config)
	: m_data(config.data)
{
	App::getInstance().getAnimationStorage().addGroup(m_data.id, this);
}

AnimationGroupConfig AnimationGroup::parseJson(const nlohmann::json& json) 
{
	return AnimationGroupConfig::fromJson(json);
}

AnimationGroupConfig AnimationGroupConfig::fromJson(const nlohmann::json& json)
{
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
