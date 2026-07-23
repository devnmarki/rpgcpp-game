#include "time.hpp"
#include "core/app.hpp"

Time::Time()
	: 
	mTargetFps(60), 
	mNsPerSecond(1'000'000'000), 
	mTargetNsPerSecond(mNsPerSecond / mTargetFps),
	mLastTime(SDL_GetTicks())
{

}

void Time::updateDeltaTime()
{
	mFrameStartNs = SDL_GetTicksNS();

	uint64_t timeDiffNS = mFrameStartNs - mLastTime;
	mDeltaTime = static_cast<float>(timeDiffNS) / static_cast<float>(mNsPerSecond);
	mLastTime = mFrameStartNs;

	if (mDeltaTime > 0.1f)
		mDeltaTime = 0.1f;
}

void Time::updateFps()
{
	mFrameCounter++;
	mFpsTimer += mDeltaTime;
	if (mFpsTimer >= 1.0f) {
		int currentFPS = static_cast<int>(mFrameCounter / mFpsTimer);
		SDL_SetWindowTitle(App::getInstance().getWindow().getHandle(), (App::getInstance().getWindow().getTitle() + " | FPS: " + std::to_string(currentFPS)).c_str());
		mFrameCounter = 0;
		mFpsTimer = 0.0f;
	}

	uint64_t workTimeNS = SDL_GetTicksNS() - mFrameStartNs;
	if (workTimeNS < mTargetNsPerSecond) {
		SDL_DelayNS(mTargetNsPerSecond - workTimeNS);
	}
}