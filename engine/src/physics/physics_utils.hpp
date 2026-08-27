#ifndef PHYSICSUTILS_HPP
#define PHYSICSUTILS_HPP

#include <box2d/box2d.h>
#include <glm/glm.hpp>

class PhysicsUtils {
public:
	inline static const float PIXELS_PER_METER = 16.0f;

	static float toMeters(float pixels) { return pixels / PIXELS_PER_METER; }
	static glm::vec2 toMeters(const glm::vec2& pixels) { return pixels / PIXELS_PER_METER; }
	static b2Vec2 toMeters(const b2Vec2& pixels) { return { pixels.x / PIXELS_PER_METER, pixels.y / PIXELS_PER_METER }; }

	static float toPixels(float meters) { return meters * PIXELS_PER_METER; }
	static glm::vec2 toPixels(const glm::vec2& meters) { return meters * PIXELS_PER_METER; }
	static b2Vec2 toPixels(const b2Vec2& meters) { return { meters.x * PIXELS_PER_METER, meters.y * PIXELS_PER_METER }; }
};

#endif