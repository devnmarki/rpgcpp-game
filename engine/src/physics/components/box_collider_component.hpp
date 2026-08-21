#ifndef BOXCOLLIDERCOMPONENT_HPP
#define BOXCOLLIDERCOMPONENT_HPP

#include <box2d/box2d.h>
#include <glm/glm.hpp>

//struct BoxColliderComponent {
//public:
//	glm::vec2 size = { 32.f, 32.f };
//	glm::vec2 offset = { 0.f, 0.f };
//	bool isTrigger = false;
//
//	BoxColliderComponent() = default;
//	BoxColliderComponent(
//		const glm::vec2& psize = { 32.f, 32.f },
//		const glm::vec2& poffset = { 0.f, 0.f },
//		bool pisTrigger = false
//	) : size(psize), offset(poffset), isTrigger(pisTrigger) { }
//
//	bool hasBody() const { return B2_IS_NON_NULL(m_bodyId); }
//
//private:
//	b2BodyId m_bodyId = b2_nullBodyId;
//
//	friend class PhysicsSystem;
//	friend class RenderSystem;
//};

struct BoxColliderComponent {
	glm::vec2 size = { 32.f, 32.f };
	glm::vec2 offset = { 0.f, 0.f };
	bool isTrigger = false;
	b2BodyId bodyId = b2_nullBodyId;

	bool hasBody() const { return B2_IS_NON_NULL(bodyId); }
};

#endif