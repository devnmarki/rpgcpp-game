#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <string>
#include <vector>
#include <algorithm>

struct AnimationData {
	std::string id = "";
	std::string spriteSheetId = "";
	std::vector<int> frames;
	float frameDuration = 0.1f;
	bool loop = true;
};

class Animation {
public:
	Animation() = default;
	explicit Animation(const AnimationData& data);

	void play();

	AnimationData& getData() { return m_data; }
	const AnimationData& getData() const { return m_data; }
	int getCurrentFrame() const { return m_currentFrame; }
	float getFrameTime() const { return m_frameTime; }

private:
	AnimationData m_data;
	int m_currentFrame = 0;
	float m_frameTime = 0.0f;
};

#endif