#ifndef DEFAULTSCENE_HPP
#define DEFAULTSCENE_HPP

#include "core/engine.hpp"

class DefaultScene : public Scene {
public:
	DefaultScene() = default;

	void onEnter() override;
	void onRender() override;

private:
	std::shared_ptr<Sprite> m_pSprite;
};

#endif