#include "SystemDrawable.h"
#include "../Managers/SystemManager.h"
#include "../Entity.h"
#include "../Window.h"

SystemDrawable::SystemDrawable(SystemType type)
	: SystemBase(type)
{
}

void SystemDrawable::draw(const Window & window) const
{
	for(const auto& drawableComponent : SystemManager::getInstance().m_drawableComponents)
	{ 
		window.blit(drawableComponent.m_sprite);
	}
}
