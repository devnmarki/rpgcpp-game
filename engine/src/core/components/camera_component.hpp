#ifndef CAMERACOMPONENT_HPP
#define CAMERACOMPONENT_HPP

#include <glm/glm.hpp>

#include "transform_component.hpp"

struct CameraComponent {
	glm::vec2 viewportSize{ 1280.f, 720.f };
	glm::vec2 position{ 0.f, 0.f };
	
	float zoom = 1.0f;
	float minZoom = 0.5f;
	float maxZoom = 3.0f;
	
	TransformComponent* target = nullptr;
	float damping = 8.0f;
};

#endif