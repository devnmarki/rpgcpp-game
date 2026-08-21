#ifndef RIGIDBODYCOMPONENT_HPP
#define RIGIDBODYCOMPONENT_HPP

#include <box2d/box2d.h>

struct RigidBodyComponent {
	float mass = 1.0f;
	float gravityScale = 1.0f;
	glm::vec2 velocity = { 0.f, 0.f };
};

#endif