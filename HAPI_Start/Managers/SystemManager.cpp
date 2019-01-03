#include "SystemManager.h"
#include "EntityManager.h"
#include "../Systems/SystemPlayer.h"
#include "../Systems/SystemMovable.h"
#include "../Systems/SystemDrawable.h"
#include "../Systems/SystemPosition.h"
#include "../EntityNameConverter.h"
#include "../Utilities.h"

std::array<std::unique_ptr<SystemBase>, TotalSystems> assignSystems()
{
	std::array<std::unique_ptr<SystemBase>, TotalSystems> systems;
	systems[static_cast<int>(SystemType::Player)] = std::make_unique<SystemPlayer>(SystemType::Player);
	systems[static_cast<int>(SystemType::Movable)] = std::make_unique<SystemMovable>(SystemType::Movable);
	systems[static_cast<int>(SystemType::Drawable)] = std::make_unique<SystemDrawable>(SystemType::Drawable);
	systems[static_cast<int>(SystemType::Position)] = std::make_unique<SystemPlayer>(SystemType::Position);

	return systems;
}

SystemManager::SystemManager()
	: m_systems(assignSystems()),
	m_positionComponents(MAX_ENTITIES, ComponentPosition(ComponentType::Position)),
	m_drawableComponents(MAX_ENTITIES, ComponentDrawable(ComponentType::Drawable)),
	m_movableComponents(MAX_ENTITIES, ComponentMovable(ComponentType::Movable)),
	m_systemMessages()
{}

void SystemManager::initializeComponentsToEntity(const std::vector<ComponentType>& entityComponents, const Entity& entity)
{
	for (ComponentType entityComponent : entityComponents)
	{
		switch (entityComponent)
		{
		case ComponentType::Position :
		{
			assert(m_positionComponents[entity.m_ID].m_owningEntityID == ENTITY_NOT_IN_USE);
			m_positionComponents[entity.m_ID].m_owningEntityID = entity.m_ID;
			break;
		}
		case ComponentType::Drawable :
		{
			assert(m_drawableComponents[entity.m_ID].m_owningEntityID == ENTITY_NOT_IN_USE);
			m_drawableComponents[entity.m_ID].m_owningEntityID = entity.m_ID;
			break;
		}
		case ComponentType::Animation :
		{
			assert(m_animationComponents[entity.m_ID].m_owningEntityID == ENTITY_NOT_IN_USE);
			m_animationComponents[entity.m_ID].m_owningEntityID = entity.m_ID;
			break;
		}
		case ComponentType::Movable :
		{
			assert(m_movableComponents[entity.m_ID].m_owningEntityID == ENTITY_NOT_IN_USE);
			m_movableComponents[entity.m_ID].m_owningEntityID = entity.m_ID;
			break;
		}
		}
	}
}

void SystemManager::handleSystemMessages()
{
	if (m_systemMessages.empty())
	{
		return;
	}

	for (const auto& systemMessage : m_systemMessages)
	{
		if (systemMessage.m_destination == SystemType::Global)
		{
			for (const auto& system : m_systems)
			{
				system->onSystemMessage(systemMessage);
			}
		}
		else
		{
			m_systems[static_cast<int>(systemMessage.m_destination)]->onSystemMessage(systemMessage);
		}
	}

	m_systemMessages.clear();
}

void SystemManager::handleSpecializedMessages()
{

}

void SystemManager::addSpecializedSystemMessage(const SystemSpecializedMessage<Vector2i>& message)
{
}

void SystemManager::addSystemMessage(const SystemMessage & message)
{
	m_systemMessages.push_back(message);
}

void SystemManager::sendInstantSystemMessage(const SystemMessage & message) const
{
	for (const auto& system : m_systems)
	{
		system->onSystemMessage(message);
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

void SystemManager::update(const std::vector<Entity*>& entities)
{
	handleSystemMessages();

	for (const auto& system : m_systems)
	{
		system->update(entities);
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