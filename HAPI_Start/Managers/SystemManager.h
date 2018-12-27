#pragma once

#include "../Components/ComponentPosition.h"
#include "../Components/ComponentDrawable.h"
#include "../Components/ComponentMovable.h"
#include "../Systems/SystemMessage.h"
#include <vector>
#include <algorithm>
#include <assert.h>
#include <list>

class SystemManager
{
public:
	static SystemManager& getInstance()
	{
		static SystemManager systemManager;
		return systemManager;
	}

	SystemManager(const SystemManager&) = delete;
	SystemManager& operator=(const SystemManager&) = delete;
	SystemManager(SystemManager&&) = delete;
	SystemManager&& operator=(SystemManager&&) = delete;

	void assignEntityToComponents(const std::array<ComponentType, TotalComponents>& entityComponents, int entityID);

	template <class Component>
	Component& getEntityComponent(int entityID, ComponentType componentType) const
	{
		switch (componentType)
		{
		case ComponentType::Position :
		{
			return getComponent<ComponentPosition>(m_positionComponents, entityID);
			break;
		}
		case ComponentType::Drawable :
		{

			break;
		}
		case ComponentType::Movable :
		{

			break;
		}
		}
	}

private:
	SystemManager();
	std::vector<ComponentPosition> m_positionComponents;
	std::vector<ComponentDrawable> m_drawableComponents;
	std::vector<ComponentMovable> m_movableComponents;
	std::list<SystemMessage> m_systemMessages;

	template <class Component>
	void assignEntityIDToComponent(std::vector<Component>& componentContainer, int entityID)
	{
		auto iter = std::find_if(componentContainer.begin(), componentContainer.end(),
			[](const auto& component) { return component.m_owningEntityID == ENTITY_NOT_IN_USE; });
		assert(iter != componentContainer.cend());
		iter->m_owningEntityID = entityID;
	}

	template <class Component>
	Component getComponent(std::vector<Component>& components, int entityID) const
	{
		auto iter = std::find_if(components.begin(), components.end(),
			[entityID](const auto& component) { return component.m_owningEntityID == entityID; });
		assert(iter != components.cend());
		return iter;
	}
};