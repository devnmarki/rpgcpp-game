#include "animation_storage.hpp"
#include "core/app.hpp"

void AnimationStorage::addGroup(const std::string& groupId, AnimationGroup* group)
{
    if (!group) {
        spdlog::error("Tried to add null AnimationGroup for groupId: '{}'", groupId);
        return;
    }

    const AnimationGroupData& groupData = group->getData();

    for (const auto& [animName, animObj] : groupData.animations) {
        std::shared_ptr<Animation> animation = std::make_shared<Animation>(animObj);
        std::string fullId = getFullAnimationId(groupId, animName);

        auto [it, success] = m_animations.insert({ fullId, animation });
        if (!success) {
            spdlog::warn("Animation '{}' already exists!", fullId);
            continue;
        }
    }
}
Animation AnimationStorage::get(const std::string& groupId, const std::string& id)
{
	std::string fullId = getFullAnimationId(groupId, id);

	auto it = m_animations.find(fullId);
	if (it == m_animations.end()) {
	    spdlog::error("There is no animation '{}'!", fullId);
        return Animation{};
	}

	return *it->second;
}

const AnimationData* AnimationStorage::getAnimationData(const std::string& groupId, const std::string& id)
{
    std::string fullId = getFullAnimationId(groupId, id);

    auto it = m_animations.find(fullId);
    if (it == m_animations.end()) {
        spdlog::error("There is no animation '{}'!", fullId);
        return nullptr;
    }

    return &it->second->getData();
}

std::string AnimationStorage::getFullAnimationId(const std::string& groupId, const std::string& id)
{
	return groupId + "_" + id;
}