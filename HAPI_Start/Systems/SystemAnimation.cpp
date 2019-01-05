#include "SystemAnimation.h"
#include "../Managers/SystemManager.h"
#include "../Managers/EntityManager.h"

void SystemAnimation::update(float deltaTime) const
{
	for (auto& componentAnimation : SystemManager::getInstance().getAllAnimationComponents())
	{
		if (componentAnimation.m_owningEntityID == ENTITY_ID_NULL)
		{
			continue;
		}

		
	}
}