#include "animation.hpp"
#include "core/app.hpp"

Animation::Animation(const AnimationData& data)
	: m_data(data)
{

}

void Animation::play()
{
	float dt = App::getInstance().getTime().getDeltaTime();

	m_frameTime += dt;
	if (m_frameTime >= m_data.frameDuration) {
		m_frameTime = 0.0f;

		if (m_data.frames.empty())
			return;
		
		if (m_data.loop)
			m_currentFrame = (m_currentFrame + 1) % m_data.frames.size();
		else
			m_currentFrame = std::min(m_currentFrame + 1, static_cast<int>(m_data.frames.size() - 1));
	}
}