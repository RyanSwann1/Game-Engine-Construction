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
	}
}
