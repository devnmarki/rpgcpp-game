#include "time.hpp"
#include "core/app.hpp"

Time::Time()
	: 
	m_targetFps(60), 
	m_nsPerSecond(1'000'000'000), 
	m_targetNsPerSecond(m_nsPerSecond / m_targetFps),
	m_lastTime(SDL_GetTicks())
{

}

void Time::updateDeltaTime()
{
	m_frameStartNs = SDL_GetTicksNS();

	uint64_t timeDiffNS = m_frameStartNs - m_lastTime;
	m_deltaTime = static_cast<float>(timeDiffNS) / static_cast<float>(m_nsPerSecond);
	m_lastTime = m_frameStartNs;

	if (m_deltaTime > 0.1f)
		m_deltaTime = 0.1f;
}

void Time::updateFps()
{
	m_frameCounter++;
	m_fpsTimer += m_deltaTime;
	if (m_fpsTimer >= 1.0f) {
		int currentFPS = static_cast<int>(m_frameCounter / m_fpsTimer);
		SDL_SetWindowTitle(App::getInstance().getWindow().getHandle(), (App::getInstance().getWindow().getTitle() + " | FPS: " + std::to_string(currentFPS)).c_str());
		m_frameCounter = 0;
		m_fpsTimer = 0.0f;
	}

	uint64_t workTimeNS = SDL_GetTicksNS() - m_frameStartNs;
	if (workTimeNS < m_targetNsPerSecond) {
		SDL_DelayNS(m_targetNsPerSecond - workTimeNS);
	}
}