#include "SystemManager.h"
#include "EntityManager.h"
#include "../Systems/SystemPlayer.h"
#include "../Systems/SystemMovable.h"
#include "../Systems/SystemDrawable.h"
#include "../Systems/SystemPosition.h"
#include "../Systems/SystemAnimation.h"
#include "../EntityNameConverter.h"
#include "../Utilities.h"
#include "../Systems/SystemMessage.h"

std::array<std::unique_ptr<SystemBase>, TotalSystems> assignSystems()
{
	std::array<std::unique_ptr<SystemBase>, TotalSystems> systems;
	systems[static_cast<int>(SystemType::Player)] = std::make_unique<SystemPlayer>();
	systems[static_cast<int>(SystemType::Movable)] = std::make_unique<SystemMovable>();
	systems[static_cast<int>(SystemType::Drawable)] = std::make_unique<SystemDrawable>();
	systems[static_cast<int>(SystemType::Position)] = std::make_unique<SystemPosition>();
	systems[static_cast<int>(SystemType::Animation)] = std::make_unique<SystemAnimation>();

	return systems;
}

SystemManager::SystemManager()
	: m_systems(assignSystems()),
	m_positionComponents(MAX_ENTITIES, ComponentPosition()),
	m_drawableComponents(MAX_ENTITIES, ComponentDrawable()),
	m_movableComponents(MAX_ENTITIES, ComponentMovable()),
	m_animationComponents(MAX_ENTITIES, ComponentAnimation())
{}

void SystemManager::initializeComponentsToEntity(const std::vector<ComponentType>& entityComponents, const Entity& entity)
{
	for (ComponentType entityComponent : entityComponents)
	{
		switch (entityComponent)
		{
		case ComponentType::Position :
		{
			assert(m_positionComponents[entity.m_ID].m_owningEntityID == ENTITY_ID_NULL);
			m_positionComponents[entity.m_ID].m_owningEntityID = entity.m_ID;
			break;
		}
		case ComponentType::Drawable :
		{
			assert(m_drawableComponents[entity.m_ID].m_owningEntityID == ENTITY_ID_NULL);
			m_drawableComponents[entity.m_ID].m_owningEntityID = entity.m_ID;
			break;
		}
		case ComponentType::Animation :
		{
			assert(m_animationComponents[entity.m_ID].m_owningEntityID == ENTITY_ID_NULL);
			m_animationComponents[entity.m_ID].m_owningEntityID = entity.m_ID;
			break;
		}
		case ComponentType::Movable :
		{
			assert(m_movableComponents[entity.m_ID].m_owningEntityID == ENTITY_ID_NULL);
			m_movableComponents[entity.m_ID].m_owningEntityID = entity.m_ID;
			break;
		}
		}
	}
}

void SystemManager::sendSpecializedSystemMessage(const SystemSpecializedMessage<Vector2i>& message)
{

}

void SystemManager::sendSystemMessage(const SystemMessage & message)
{
	if (message.m_destination == SystemType::Global)
	{
		for (const auto& system : m_systems)
		{
			system->onSystemMessage(message);
		}
	}
	else
	{
		m_systems[static_cast<int>(message.m_destination)]->onSystemMessage(message);
	}
}

ComponentPosition & SystemManager::getComponentPosition(int entityID)
{
	assert(entityID == m_positionComponents[entityID].m_owningEntityID);
	return m_positionComponents[entityID];
}

ComponentDrawable & SystemManager::getComponentDrawable(int entityID)
{
	assert(entityID == m_drawableComponents[entityID].m_owningEntityID);
	return m_drawableComponents[entityID];
}

ComponentMovable & SystemManager::getComponentMovable(int entityID)
{
	assert(entityID == m_movableComponents[entityID].m_owningEntityID);
	return m_movableComponents[entityID];
}

ComponentAnimation & SystemManager::getComponentAnimation(int entityID)
{
	assert(entityID == m_animationComponents[entityID].m_owningEntityID);
	return m_animationComponents[entityID];
}

void SystemManager::update(float deltaTime) const
{
	for (const auto& system : m_systems)
	{
		system->update(deltaTime);
	}
}

void SystemManager::draw(const Window& window) const
{
	assert(m_systems[static_cast<int>(SystemType::Drawable)].get());
	const auto& system = m_systems[static_cast<int>(SystemType::Drawable)].get();
	static_cast<SystemDrawable*>(system)->draw(window);
}

std::vector<ComponentPosition>& SystemManager::getAllPositionComponents()
{
	return m_positionComponents;
}

std::vector<ComponentDrawable>& SystemManager::getAllDrawableComponents()
{
	return m_drawableComponents;
}

std::vector<ComponentMovable>& SystemManager::getAllMovableComponents()
{
	return m_movableComponents;
}

std::vector<ComponentAnimation>& SystemManager::getAllAnimationComponents()
{
	return m_animationComponents;
}