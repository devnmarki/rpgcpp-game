#ifndef CORECOMPONENTS_HPP
#define CORECOMPONENTS_HPP

#include <glm/glm.hpp>

struct TransformComponent {
	glm::vec2 position = { 0.0f, 0.0f };
	glm::vec2 scale = { 0.0f, 0.0f };
	float rotation = 0.0f;
};

#endif