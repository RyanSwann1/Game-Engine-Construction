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

	std::vector<ComponentPosition>& getAllPositionComponents();
	std::vector<ComponentDrawable>& getAllDrawableComponents();
	std::vector<ComponentMovable> & getAllMovableComponents();
	std::vector<ComponentAnimation>& getAllAnimationComponents();

	ComponentPosition& getComponentPosition(int entityID);
	ComponentDrawable& getComponentDrawable(int entityID);
	ComponentMovable& getComponentMovable(int entityID);

	void initializeComponentsToEntity(const std::vector<ComponentType>& entityComponents, const Entity& entity);
	void addSpecializedSystemMessage(const SystemSpecializedMessage<Vector2i>& message);
	void addSystemMessage(const SystemMessage& message);
	void sendInstantSystemMessage(const SystemMessage& message) const;
	void update(const std::vector<Entity*>& entities);
	void draw(const Window& window) const;

private:
	SystemManager();
	const std::array<std::unique_ptr<SystemBase>, TotalSystems> m_systems;
	std::vector<ComponentPosition> m_positionComponents;
	std::vector<ComponentDrawable> m_drawableComponents;
	std::vector<ComponentMovable> m_movableComponents;
	std::vector<ComponentAnimation> m_animationComponents;
	std::vector<SystemMessage> m_systemMessages;
	std::vector<SystemSpecializedMessage<Vector2i>> m_systemPositionMessages;

	void handleSystemMessages();
	void handleSpecializedMessages();

	template <class Component>
	void assignEntityIDToComponent(std::vector<Component>& componentContainer, int entityID)
	{
		static_cast<Component>(componentContainer[entityID]).m_owningEntityID = entityID;
		//auto iter = std::find_if(componentContainer.begin(), componentContainer.end(),
		//	[](const auto& component) { return component.m_owningEntityID == ENTITY_NOT_IN_USE; });
		//assert(iter != componentContainer.cend());
		//iter->m_owningEntityID = entityID;
	}
};