#ifndef CAMERAENTITY_HPP
#define CAMERAENTITY_HPP

#include "ecs/world.hpp"
#include "ecs/components.hpp"

class CameraEntity {
public:
	static Entity create(World& world) {
		Entity camera = world.createEntity();

		camera.addComponent<TransformComponent>();
		camera.addComponent<CameraComponent>();

		return camera;
	}
};

// return worldPos - cam.position + glm::vec2(screenW * 0.5f, screenH * 0.5f);

#endif