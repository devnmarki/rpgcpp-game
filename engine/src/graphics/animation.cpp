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
	}
}