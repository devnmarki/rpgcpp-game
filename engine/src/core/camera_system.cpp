#include "camera_system.hpp"
#include "ecs/world.hpp"

CameraSystem::CameraSystem(World* world, SystemPhase phase)
	: System(world, phase)
{

}

void CameraSystem::tick(float dt)
{
	getWorld()->query<TransformComponent, CameraComponent>([](Entity, TransformComponent& transform, CameraComponent& camera) {
		camera.position = transform.position;
	
		camera.zoom = std::clamp(camera.zoom, camera.minZoom, camera.maxZoom);
	});
}
