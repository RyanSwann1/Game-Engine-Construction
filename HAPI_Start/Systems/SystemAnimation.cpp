#include "SystemAnimation.h"
#include "../Managers/SystemManager.h"

SystemAnimation::SystemAnimation(SystemType type)
	: SystemBase(type)
{
}

void SystemAnimation::update(const std::vector<Entity*>& entities) const
{
	for (auto& componentAnimation : SystemManager::getInstance().m_animationComponents)
	{
		componentAnimation.m_animationPlayer.update();
	}
}

void SystemAnimation::draw(const Window & window) const
{
	for (const auto& componentAnimation : SystemManager::getInstance().m_animationComponents)
	{
		componentAnimation.m_animationPlayer.draw(window);
	}
}
