#ifndef ANIMATORCOMPONENT_HPP
#define ANIMATORCOMPONENT_HPP

#include <unordered_map>
#include <string>

#include "graphics/animation.hpp"

struct AnimatorComponent {
	std::string groupId = "";
	std::string currentAnimationId = "";

	Animation activeAnimation;
	bool initialized = false;
};

struct AnimationSwitchComponent {
	std::string nextAnimation = "";
};

#endif