#include "SystemAnimation.h"
#include "../Managers/SystemManager.h"
#include "../Managers/EntityManager.h"
#include "SystemMessage.h"

void SystemAnimation::update(float deltaTime) const
{
	for (auto& componentAnimation : SystemManager::getInstance().getAllAnimationComponents())
	{
		if (componentAnimation.m_owningEntityID == ENTITY_ID_NULL)
		{
			continue;
		}

		auto& entitySprite = SystemManager::getInstance().getDrawableComponent(componentAnimation.m_owningEntityID).m_sprite;
		componentAnimation.m_animationPlayer.update(entitySprite.m_rect, deltaTime);
	}
}

void SystemAnimation::onSystemMessage(const SystemMessage & message) const
{
	auto& componentAnimation = SystemManager::getInstance().getAnimationComponent(message.m_entityID);
	auto& componentDrawable = SystemManager::getInstance().getDrawableComponent(message.m_entityID);
	switch (message.m_action)
	{
	case SystemAction::LoadInEntityAnimations :
	{
		componentAnimation.m_animationPlayer.initialize(message.m_entityName);
		break;
	}
	case SystemAction::InitializeEntityAnimation :
	{
		componentAnimation.m_animationPlayer.switchToAnimation(componentDrawable.m_sprite.m_rect, AnimationName::Default);
		break;
	}
	case SystemAction::MoveEntityLeft :
	{
		componentAnimation.m_animationPlayer.switchToAnimation(componentDrawable.m_sprite.m_rect, AnimationName::WalkingLeft);
		break;
	}
	case SystemAction::MoveEntityRight :
	{
		componentAnimation.m_animationPlayer.switchToAnimation(componentDrawable.m_sprite.m_rect, AnimationName::WalkingRight);
		break;
	}
	case SystemAction::MoveEntityUp :
	{
		componentAnimation.m_animationPlayer.switchToAnimation(componentDrawable.m_sprite.m_rect, AnimationName::WalkingUp);
		break;
	}
	case SystemAction::MoveEntityDown :
	{
		componentAnimation.m_animationPlayer.switchToAnimation(componentDrawable.m_sprite.m_rect, AnimationName::WalkingDown);
		break;
	}
	}
}