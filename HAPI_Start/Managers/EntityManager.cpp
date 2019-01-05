#include "EntityManager.h"
#include "../Components/ComponentDrawable.h"
#include "../Components/ComponentPosition.h"
#include "SystemManager.h"
#include "../Systems/SystemMessage.h"
#include <utility>
#include <array>

constexpr unsigned int TOTAL_PLAYER = 1;
constexpr unsigned int TOTAL_PROJECTILES = 50;
constexpr unsigned int TOTAL_ENEMIES = 20;

std::unordered_map<EntityName, std::vector<ComponentType>> assignEntityFactory()
{
	std::unordered_map<EntityName, std::vector<ComponentType>> entityComponents;

	entityComponents.emplace(EntityName::Projectile, 
		std::vector<ComponentType>{ ComponentType::Position, ComponentType::Drawable,  ComponentType::Movable });

	entityComponents.emplace(EntityName::Player, 
		std::vector<ComponentType>{ ComponentType::Drawable, ComponentType::Position, ComponentType::Movable , ComponentType::Animation });

	entityComponents.emplace(EntityName::Enemy, 
		std::vector<ComponentType>{ ComponentType::Drawable, ComponentType::Position, ComponentType::Movable });

	return entityComponents;
}

//Entity Pool
EntityManager::EntityFactory::EntityFactory()
	: m_entityFactory(assignEntityFactory()),
	m_entityPool(),
	m_entityCount(0)
{
	m_entityPool.reserve(MAX_ENTITIES);

	//load in player(s)
	for (int i = 0; i < TOTAL_PLAYER; ++i)
	{
		createEntity(EntityName::Player);
	}

	////Load in projectiles
	//for (int i = 0; i < TOTAL_PROJECTILES; ++i)
	//{
	//	createEntity(EntityName::Projectile);
	//}

	////load in enemies
	//for (int i = 0; i < TOTAL_ENEMIES; ++i)
	//{
	//	createEntity(EntityName::Enemy);
	//}
}

Entity * EntityManager::EntityFactory::getEntity(EntityName name)
{
	Entity* availableEntity = nullptr;
	for (auto& entity : m_entityPool)
	{
		if (entity.m_inUse || entity.m_name != name)
		{
			continue;
		}
		availableEntity = &entity;
		break;
	}

	return availableEntity;
}

const std::vector<ComponentType>& EntityManager::EntityFactory::getEntityComponents(EntityName name) const
{
	auto iter = m_entityFactory.find(name);
	assert(iter != m_entityFactory.cend());
	return iter->second;
}

void EntityManager::EntityFactory::createEntity(EntityName name)
{
	const Entity entity(name, m_entityCount);
	SystemManager::getInstance().initializeComponentsToEntity(getEntityComponents(entity.m_name), entity);
	SystemManager::getInstance().sendSystemMessage(
		SystemMessage(entity.m_ID, entity.m_name, SystemAction::InitializeEntityAnimations, SystemType::Animation));
	m_entityPool.push_back(entity);

	++m_entityCount;
}

//EntityManager
EntityManager::EntityManager()
	: m_entityFactory(),
	m_entitiesToAdd(),
	m_entities(),
	m_entitiesToRemove()
{}

const Entity & EntityManager::getEntity(int entityID) const
{
	auto iter = std::find_if(m_entities.cbegin(), m_entities.cend(), [entityID](const auto& entity) { return entity->m_ID == entityID; });
	assert(iter != m_entities.cend());
	return *(*iter);
}

const std::vector<Entity*>& EntityManager::getEntities() const
{
	assert(!m_entities.empty());
	return m_entities;
}

void EntityManager::addEntity(EntityName name, Vector2i startingPosition)
{
	m_entitiesToAdd.emplace_back(name, startingPosition);
}
  
void EntityManager::removeEntity(int entityID)
{
	m_entitiesToRemove.push_back(entityID);
}

void EntityManager::update()
{
	handleEntityAdditions();
	handleEntityRemovals();
}

void EntityManager::handleEntityRemovals()
{
	for (int entityIDToRemove : m_entitiesToRemove)
	{
		auto entity = std::find_if(m_entities.begin(), m_entities.end(),
			[entityIDToRemove](const auto& entity) { return entity->m_ID == entityIDToRemove; });
		assert(entity != m_entities.cend());
		(*entity)->m_inUse = false;

		m_entities.erase(entity);
	}

	m_entitiesToRemove.clear();
}

void EntityManager::handleEntityAdditions()
{
	for (const std::pair<EntityName, Vector2i>& entityToAdd : m_entitiesToAdd)
	{
		Entity* entity = m_entityFactory.getEntity(entityToAdd.first);
		assert(entity);
		entity->m_inUse = true;
		SystemManager::getInstance().sendSpecializedSystemMessage(
	SystemSpecializedMessage<Vector2i>(*entity, entityToAdd.second, SystemAction::SetStartingPosition, SystemType::Position));

		m_entities.push_back(entity);
	}

	m_entitiesToAdd.clear();
}