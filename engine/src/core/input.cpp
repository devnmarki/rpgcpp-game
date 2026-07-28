#include "input.hpp"

void Input::updateState()
{
	std::unordered_map<int, bool> currentKeyboardState;

	int numKeys;
	const bool* sdlKeyboardState = SDL_GetKeyboardState(&numKeys);

	for (int i = 0; i < numKeys; i++) {
		if (sdlKeyboardState[i])
			currentKeyboardState[i] = true;
	}

	m_previousKeyboardState = m_currentKeyboardState;
	m_currentKeyboardState = currentKeyboardState;
}

bool Input::isKeyDown(Keys key)
{
	auto it = m_currentKeyboardState.find(static_cast<int>(key));
	return (it != m_currentKeyboardState.end()) ? it->second : false;
}

bool Input::isKeyPressed(Keys key)
{
	bool isCurrentDown = isKeyDown(key);

	auto it = m_previousKeyboardState.find(static_cast<int>(key));
	bool wasHeld = (it != m_previousKeyboardState.end()) ? it->second : false;

	return isCurrentDown && !wasHeld;
}

bool Input::isKeyReleased(Keys key)
{
	bool isCurrentDown = isKeyDown(key);

	auto it = m_previousKeyboardState.find(static_cast<int>(key));
	bool wasHeld = (it != m_previousKeyboardState.end()) ? it->second : false;

	return !isCurrentDown && wasHeld;
}