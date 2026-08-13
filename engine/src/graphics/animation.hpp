#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <vector>
#include <string>

#include "loader/asset.hpp"

struct AnimationData {
	std::string spriteSheetId = "";
	std::vector<int> frames;
	float frameDuration = 0.1f;
	float spriteWidth = 16.0f;
	float spriteHeight = 16.0f;
};

struct AnimationConfig {

};

class Animation : public Asset {
public:

};

#endif