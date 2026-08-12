#ifndef TIME_HPP
#define TIME_HPP

#include <string>

#include <SDL3/SDL.h>

class Time {
public:
	Time();

	void updateDeltaTime();
	void updateFps();

	float getDeltaTime() { return m_deltaTime; }

private:
	uint64_t m_targetFps;
	uint64_t m_nsPerSecond;
	uint64_t m_targetNsPerSecond;
	
	uint64_t m_lastTime;
	float m_deltaTime = 0.0f;
	uint64_t m_frameStartNs = 0;

	float m_fpsTimer = 0.0f;
	int m_frameCounter = 0;
};

#endif