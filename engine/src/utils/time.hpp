#ifndef TIME_HPP
#define TIME_HPP

#include <string>

#include <SDL3/SDL.h>

class Time {
public:
	Time();

	void updateDeltaTime();
	void updateFps();

private:
	uint64_t mTargetFps;
	uint64_t mNsPerSecond;
	uint64_t mTargetNsPerSecond;
	
	uint64_t mLastTime;
	float mDeltaTime = 0.0f;
	uint64_t mFrameStartNs = 0;

	float mFpsTimer = 0.0f;
	int mFrameCounter = 0;
};

#endif