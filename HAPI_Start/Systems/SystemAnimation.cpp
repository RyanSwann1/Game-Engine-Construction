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

		auto& entitySprite = SystemManager::getInstance().getComponentDrawable(componentAnimation.m_owningEntityID).m_sprite;
		componentAnimation.m_animationPlayer.update(entitySprite.getRect(), deltaTime);
	}
}

void SystemAnimation::onSystemMessage(const SystemMessage & message) const
{
	switch (message.m_action)
	{
	case SystemAction::InitializeEntityAnimations :
	{
		auto& componentAnimation = SystemManager::getInstance().getComponentAnimation(message.m_entityID);
		componentAnimation.m_animationPlayer.initialize(message.m_entityName);
		break;
	}
	}
}
