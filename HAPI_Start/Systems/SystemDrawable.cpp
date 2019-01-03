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
	for(const auto& drawableComponent : SystemManager::getInstance().getAllDrawableComponents())
	{ 
		if (!SystemBase::isComponentInUse<ComponentDrawable>(drawableComponent))
		{
			continue;
		}

		auto& i = SystemManager::getInstance().getAllDrawableComponents();
		window.blit(drawableComponent.m_sprite);
	}
}

void SystemDrawable::onSystemMessage(const SystemMessage & systemMessage) const
{	
	switch (systemMessage.m_action)
	{
	case SystemAction::InitializeEntitySprite :
	{
		auto& drawableComponent = SystemManager::getInstance().getComponentDrawable(systemMessage.m_entity.m_ID);
		//Temporary
		if (systemMessage.m_entity.m_name == EntityName::Player)
		{
			drawableComponent.m_sprite.setTexture("playerSprite.tga");
		}
		break;
	}
	}
}
