#ifndef ANIMATIONSTORAGE_HPP
#define ANIMATIONSTORAGE_HPP

#include <unordered_map>
#include <memory>

#include <spdlog/spdlog.h>

#include "graphics/animation.hpp"
#include "graphics/animation_group.hpp"

class AnimationStorage {
public:
	AnimationStorage() = default;

	void addGroup(const std::string& groupId, AnimationGroup* group);
	Animation get(const std::string& groupId, const std::string& id);
	const AnimationData* getAnimationData(const std::string& groupId, const std::string& id);

private:
	std::string getFullAnimationId(const std::string& groupId, const std::string& id);

private:
	std::unordered_map<std::string, std::shared_ptr<Animation>> m_animations;
};

#endif