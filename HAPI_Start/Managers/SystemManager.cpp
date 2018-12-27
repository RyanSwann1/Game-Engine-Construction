#include "SystemManager.h"
#include "EntityManager.h"

SystemManager::SystemManager()
	: m_positionComponents(MAX_ENTITIES, ComponentPosition(ComponentType::Position)),
	m_drawableComponents(MAX_ENTITIES, ComponentDrawable(ComponentType::Drawable)),
	m_movableComponents(MAX_ENTITIES, ComponentMovable(ComponentType::Movable))
{}

void SystemManager::assignEntityToComponents(const std::array<ComponentType, TotalComponents>& entityComponents, int entityID)
{
	for (ComponentType entityComponent : entityComponents)
	{
		switch (entityComponent)
		{
		case ComponentType::Position :
		{
			assignEntityIDToComponent<ComponentPosition>(m_positionComponents, entityID);
			break;
		}
		case ComponentType::Drawable :
		{
			assignEntityIDToComponent<ComponentDrawable>(m_drawableComponents, entityID);
			break;
		}
		}
	}
}