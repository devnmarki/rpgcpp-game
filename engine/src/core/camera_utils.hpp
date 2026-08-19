#ifndef CAMERAUTILS_HPP
#define CAMERAUTILS_HPP

#include <glm/glm.hpp>

#include "core/camera_entity.hpp"

inline glm::vec2 getViewSize(const CameraComponent& cam) {
	return {
		cam.viewportSize.x / cam.zoom,
		cam.viewportSize.y / cam.zoom
	};
}

inline glm::vec2 worldToScreen(const glm::vec2& worldPos, const CameraComponent& cam) {
	glm::vec2 viewSize = getViewSize(cam);
	glm::vec2 topLeft = cam.position - viewSize * 0.5f;

	return (worldPos - topLeft) * cam.zoom;
}

inline glm::vec2 screenToWorld(const glm::vec2& screenPos, const CameraComponent& cam) {
	glm::vec2 viewSize = getViewSize(cam);
	glm::vec2 topLeft = cam.position - viewSize * 0.5f;

	return topLeft + screenPos / cam.zoom;
}

#endif