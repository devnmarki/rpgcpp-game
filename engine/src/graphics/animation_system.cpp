#include "animation_system.hpp"
#include "core/app.hpp"

AnimationSystem::AnimationSystem(World* world, SystemPhase phase)
	: System(world, phase)
{

}

void AnimationSystem::tick(float dt)
{
	getWorld()->query<AnimatorComponent>([](Entity entity, AnimatorComponent& animator) {
		Animation* activeAnimation = App::getInstance().getAnimationStorage().get(animator.groupId, animator.currentAnimationId);
		if (!activeAnimation)
			return;

		activeAnimation->play();
	});

	getWorld()->query<AnimatorComponent, SpriteRendererComponent>([](Entity entity, AnimatorComponent& animator, SpriteRendererComponent& sr) {
		Animation* activeAnimation = App::getInstance().getAnimationStorage().get(animator.groupId, animator.currentAnimationId);
		if (!activeAnimation)
			return;

		SpriteSheet* animationSheet = App::getInstance().getAssetLoader().get<SpriteSheet>(activeAnimation->getData().spriteSheetId);
		if (!animationSheet)
			return;

		std::string currentFrameSpriteId = animationSheet->getSpriteId(activeAnimation->getData().frames[activeAnimation->getCurrentFrame()]);
		sr.spriteId = currentFrameSpriteId;
	});

	getWorld()->query<AnimatorComponent, AnimationSwitchComponent>
		([](Entity entity, AnimatorComponent& animator, AnimationSwitchComponent& animationSwitch) {
		animator.currentAnimationId = animationSwitch.nextAnimation;
		entity.removeComponent<AnimationSwitchComponent>();
	});
}
