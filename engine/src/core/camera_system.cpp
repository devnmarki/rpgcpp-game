#include "camera_system.hpp"
#include "ecs/world.hpp"

CameraSystem::CameraSystem(World* world, SystemPhase phase)
	: System(world, phase)
{

}

void CameraSystem::tick(float dt)
{
	getWorld()->query<TransformComponent, CameraComponent>([&dt](Entity, TransformComponent& transform, CameraComponent& camera) {
		if (camera.target) {
			float t = 1.0f - std::exp(-camera.damping * dt);
			transform.position = glm::mix(transform.position, camera.target->position, t);
		}
		
		if (!camera.target) {
			if (Input::isKeyDown(Keys::A))
				transform.position.x -= 5.0f;
			if (Input::isKeyDown(Keys::D))
				transform.position.x += 5.0f;
			if (Input::isKeyDown(Keys::W))
				transform.position.y -= 5.0f;
			if (Input::isKeyDown(Keys::S))
				transform.position.y += 5.0f;
		}

		camera.position = transform.position;

		camera.zoom = std::clamp(camera.zoom, camera.minZoom, camera.maxZoom);
	});
}
