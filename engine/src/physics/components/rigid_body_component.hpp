#ifndef RIGIDBODYCOMPONENT_HPP
#define RIGIDBODYCOMPONENT_HPP

#include <box2d/box2d.h>

struct RigidBodyComponent {
	b2BodyId bodyId = b2_nullBodyId;
	float mass = 1.f;
};

#endif