#include "animation_system.hpp"
#include "core/app.hpp"

AnimationSystem::AnimationSystem(World* world, SystemPhase phase)
	: System(world, phase)
{

}

void AnimationSystem::tick(float dt)
{
	getWorld()->query<AnimatorComponent, AnimationSwitchComponent>
		([](Entity entity, AnimatorComponent& animator, AnimationSwitchComponent& animationSwitch) {
		animator.currentAnimationId = animationSwitch.nextAnimation;

		const auto* data = App::getInstance().getAnimationStorage().getAnimationData(animator.groupId, animator.currentAnimationId);
		if (data) {
			animator.activeAnimation = Animation(*data);
		}

		entity.removeComponent<AnimationSwitchComponent>();
	});

	getWorld()->query<AnimatorComponent>([](Entity entity, AnimatorComponent& animator) {
		animator.activeAnimation.play();
	});

	getWorld()->query<AnimatorComponent, SpriteRendererComponent>([](Entity entity, AnimatorComponent& animator, SpriteRendererComponent& sr) {
		SpriteSheet* animationSheet = App::getInstance().getAssetLoader().get<SpriteSheet>(animator.activeAnimation.getData().spriteSheetId);
		if (!animationSheet)
			return;

		int currentFrameIndex = animator.activeAnimation.getData().frames[animator.activeAnimation.getCurrentFrame()];
		std::string currentFrameSpriteId = animationSheet->getSpriteId(currentFrameIndex);

		sr.spriteId = currentFrameSpriteId;
	});	
}
