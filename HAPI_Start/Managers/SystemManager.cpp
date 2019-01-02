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
	systems[static_cast<int>(SystemType::Drawable)] = std::make_unique<SystemPlayer>(SystemType::Drawable);
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

void SystemManager::initializeComponentsToEntity(const std::array<ComponentType, TotalComponents>& entityComponents, const Entity& entity)
{
	for (ComponentType entityComponent : entityComponents)
	{
		switch (entityComponent)
		{
		case ComponentType::Position :
		{
			assignEntityIDToComponent<ComponentPosition>(m_positionComponents, entity.m_ID);
			break;
		}
		case ComponentType::Drawable :
		{
			assignEntityIDToComponent<ComponentDrawable>(m_drawableComponents, entity.m_ID);
			break;
		}
		case ComponentType::Animation :
		{
			assignEntityIDToComponent<ComponentAnimation>(m_animationComponents, entity.m_ID);

			break;
		}
		case ComponentType::Movable :
		{
			assignEntityIDToComponent<ComponentMovable>(m_movableComponents, entity.m_ID);
			break;
		}
		}
	}

	m_systemMessages.emplace_back(entity, SystemAction::InitializeEntity, SystemType::Global);
}

void SystemManager::handleSystemMessages()
{

}

void SystemManager::handleGeneralMessages()
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
				system->onSystemMessage(systemMessage.m_message, systemMessage.m_entityID);
			}
		}
		else
		{
			m_systems[static_cast<int>(systemMessage.m_destination)]->onSystemMessage(systemMessage.m_message, systemMessage.m_entityID);
		}
	}

	m_systemMessages.clear();
}

void SystemManager::handleSpecializedMessages()
{

}

void SystemManager::addSystemMessage(SystemAction message, int entityID, SystemType type)
{
	m_systemMessages.emplace_back(message, entityID, type);
}

void SystemManager::addSpecializedSystemMessage(const SystemSpecializedMessage<Vector2i>& message)
{
}

void SystemManager::addGeneralSystemMessage(const SystemGeneralMessage & message)
{
}

ComponentPosition & SystemManager::getEntityComponentPosition(int entityID)
{
	assert(entityID == m_positionComponents[entityID].m_owningEntityID);
	return m_positionComponents[entityID];
}

ComponentDrawable & SystemManager::getEntityComponentDrawable(int entityID)
{
	assert(entityID == m_drawableComponents[entityID].m_owningEntityID);
	return m_drawableComponents[entityID];
}

ComponentMovable & SystemManager::getEntityComponentMovable(int entityID)
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