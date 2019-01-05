#include "SystemDrawable.h"
#include "../Managers/SystemManager.h"
#include "../Managers/EntityManager.h"
#include "SystemMessage.h"
#include "../Entity.h"
#include "../Window.h"

void SystemDrawable::draw(const Window & window) const
{
	//Draw Entities
	for(const auto& drawableComponent : SystemManager::getInstance().getAllDrawableComponents())
	{ 
		if (drawableComponent.m_owningEntityID == ENTITY_ID_NULL)
		{
			continue;
		}

		const auto& positionComponent = SystemManager::getInstance().getPositionComponent(drawableComponent.m_owningEntityID);
		window.draw(drawableComponent.m_sprite, positionComponent.m_position);
	}
}

void SystemDrawable::onSystemMessage(const SystemMessage & message) const
{
	switch (message.m_action)
	{
	case SystemAction::InitializeEntityTexture :
	{
		//Temporary
		if (message.m_entityName == EntityName::Player)
		{
			std::string textureName("Player");
			auto& drawableComponent = SystemManager::getInstance().getDrawableComponent(message.m_entityID);
			drawableComponent.m_sprite.setTexture("character.png");
		}
		break;
	}
	}
}
