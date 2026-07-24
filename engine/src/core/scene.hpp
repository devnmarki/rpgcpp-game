#ifndef SCENE_HPP
#define SCENE_HPP

class Scene {
public:
	Scene() = default;
	virtual ~Scene() = default;

	virtual void onEnter() {}
	virtual void onUpdate() {}
	virtual void onRender() {}
	virtual void onExit() {}
};

#endif