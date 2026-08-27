#include "trigger_system.hpp"
#include "ecs/world.hpp"
#include "core/app.hpp"

TriggerSystem::TriggerSystem(World* world, SystemPhase phase)
	: System(world, phase)
{

}

void TriggerSystem::tick(float dt)
{
	getWorld()->query<TriggerComponent, TilemapObjectComponent, BoxColliderComponent>(
		[](Entity, TriggerComponent& trigger, TilemapObjectComponent& tilemapObject, BoxColliderComponent& collider) 
	{
		std::string property = getObjectProperty(tilemapObject.data, "to")->getStringValue();
		trigger.to = property;

		glm::vec2 size = {
			tilemapObject.data.getAABB().width * global::GAME_SCALE,
			tilemapObject.data.getAABB().height * global::GAME_SCALE
		};

		if (collider.size != size) {
			collider.size = size;
			collider.offset += size * 0.5f;
		}
	});

	onTriggerEnter<TriggerComponent>([](Entity self, Entity other) {
		if (other.hasComponent<PlayerTag>()) {
			TriggerComponent& triggerComp = self.getComponent<TriggerComponent>();
			App::getInstance().getSceneManager().requestSceneSwitch(triggerComp.to);
		}
	});
}
