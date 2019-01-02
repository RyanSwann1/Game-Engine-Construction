#pragma once

#include "../Components/ComponentPosition.h"
#include "../Components/ComponentDrawable.h"
#include "../Components/ComponentMovable.h"
#include "../Components/ComponentAnimation.h"
#include "../Systems/SystemBase.h"
#include "../Systems/SystemSpecializedMessage.h"
#include <vector>
#include <algorithm>
#include <assert.h>
#include <memory>
#include <array>

class Window;
class Entity;
class SystemManager
{
	friend class SystemBase;
	friend class SystemDrawable;
	friend class SystemAnimation;
	friend class SystemMovable;
	friend class SystemPosition;

	class SystemGeneralMessage
	{
	public:
		SystemGeneralMessage(const Entity& entity, SystemAction message, SystemType messageDestination)
			: m_message(message),
			m_entity(entity),
			m_destination(messageDestination)
		{}

		const SystemAction m_message;
		const Entity& m_entity;
		const SystemType m_destination;
	};

public:
	static SystemManager& getInstance()
	{
		static SystemManager instance;
		return instance;
	}
	SystemManager(const SystemManager&) = delete;
	SystemManager& operator=(const SystemManager&) = delete;
	SystemManager(SystemManager&&) = delete;
	SystemManager&& operator=(SystemManager&&) = delete;

	void initializeComponentsToEntity(const std::array<ComponentType, TotalComponents>& entityComponents, const Entity& entity);
	void addSystemMessage(SystemAction message, int entityID, SystemType type);
	void addSpecializedSystemMessage(const SystemSpecializedMessage<Vector2i>& message);
	void addGeneralSystemMessage(const SystemGeneralMessage& message);
	void update(const std::vector<Entity*>& entities);
	void draw(const Window& window) const;

private:
	SystemManager();
	const std::array<std::unique_ptr<SystemBase>, TotalSystems> m_systems;
	std::vector<ComponentPosition> m_positionComponents;
	std::vector<ComponentDrawable> m_drawableComponents;
	std::vector<ComponentMovable> m_movableComponents;
	std::vector<ComponentAnimation> m_animationComponents;
	std::vector<SystemGeneralMessage> m_systemMessages;
	std::vector<SystemSpecializedMessage<Vector2i>> m_systemPositionMessages;

	
	ComponentPosition& SystemManager::getEntityComponentPosition(int entityID);
	ComponentDrawable& SystemManager::getEntityComponentDrawable(int entityID);
	ComponentMovable& SystemManager::getEntityComponentMovable(int entityID);

	void handleSystemMessages();
	void handleGeneralMessages();
	void handleSpecializedMessages();

	//***
	//REPLACE SEARCH WITH ASSERT SEARCH
	template <class Component>
	void assignEntityIDToComponent(std::vector<Component>& componentContainer, int entityID)
	{
		auto iter = std::find_if(componentContainer.begin(), componentContainer.end(),
			[](const auto& component) { return component.m_owningEntityID == ENTITY_NOT_IN_USE; });
		assert(iter != componentContainer.cend());
		iter->m_owningEntityID = entityID;
	}
};