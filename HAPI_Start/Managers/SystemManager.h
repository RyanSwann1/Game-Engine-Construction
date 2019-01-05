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

class SystemMessage;
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
	std::vector<ComponentMovable>& getAllMovableComponents();
	std::vector<ComponentAnimation>& getAllAnimationComponents();

	ComponentPosition& getPositionComponent(int entityID);
	ComponentDrawable& getDrawableComponent(int entityID);
	ComponentMovable& getMovableComponent(int entityID);
	ComponentAnimation& getAnimationComponent(int entityID);

	void initializeComponentsToEntity(const std::vector<ComponentType>& entityComponents, const Entity& entity);
	void sendSpecializedSystemMessage(const SystemSpecializedMessage<Vector2i>& message);
	void sendSystemMessage(const SystemMessage& message);
	void update(float deltaTime) const;
	void draw(const Window& window) const;

private:
	SystemManager();
	const std::array<std::unique_ptr<SystemBase>, TotalSystems> m_systems;
	std::vector<ComponentPosition> m_positionComponents;
	std::vector<ComponentDrawable> m_drawableComponents;
	std::vector<ComponentMovable> m_movableComponents;
	std::vector<ComponentAnimation> m_animationComponents;

	template <class Component>
	void assignEntityIDToComponent(std::vector<Component>& componentContainer, int entityID)
	{
		static_cast<Component>(componentContainer[entityID]).m_owningEntityID = entityID;
	}
};