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
	switch (message.m_action)
	{
	case SystemAction::LoadInEntityAnimations :
	{
		auto& componentAnimation = SystemManager::getInstance().getAnimationComponent(message.m_entityID);
		componentAnimation.m_animationPlayer.initialize(message.m_entityName);
		break;
	}
	case SystemAction::InitializeEntityAnimation :
	{
		auto& componentDrawable = SystemManager::getInstance().getDrawableComponent(message.m_entityID);
		auto& componentAnimation = SystemManager::getInstance().getAnimationComponent(message.m_entityID);
		componentAnimation.m_animationPlayer.switchToAnimation(componentDrawable.m_sprite.m_rect, AnimationName::WalkingDown);
		break;
	}
	}
}