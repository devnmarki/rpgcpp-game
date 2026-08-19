#ifndef MOVEMENTCOMPONENT_HPP
#define MOVEMENTCOMPONENT_HPP

#include <glm/glm.hpp>

struct MovementComponent {
	float movementSpeed = 100.0f;
	glm::vec2 velocity = glm::vec2(0.0f);
	bool isMoving = false;
	bool wasMoving = true;
};

#endif