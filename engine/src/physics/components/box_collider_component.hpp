#ifndef BOXCOLLIDERCOMPONENT_HPP
#define BOXCOLLIDERCOMPONENT_HPP

#include <box2d/box2d.h>
#include <glm/glm.hpp>

struct BoxColliderComponent {
	glm::vec2 size = { 32.f, 32.f };
	glm::vec2 offset = { 0.f, 0.f };
	bool isTrigger = false;
	b2BodyId bodyId = b2_nullBodyId;

	bool hasBody() const { return B2_IS_NON_NULL(bodyId); }
};

#endif