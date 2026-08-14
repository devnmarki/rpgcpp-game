#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <string>
#include <vector>

struct AnimationData {
	std::string id = "";
	std::string spriteSheetId = "";
	std::vector<int> frames;
	float frameDuration = 0.1f;
	bool loop = true;
};

class Animation {
public:
	explicit Animation(const AnimationData& data);

	void play();

private:
	AnimationData m_data;
	int m_currentFrame = 0;
	float m_frameTime = 0.0f;
};

#endif