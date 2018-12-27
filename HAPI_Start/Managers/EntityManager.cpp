#include "EntityManager.h"
#include "../Components/ComponentDrawable.h"
#include "../Components/ComponentPosition.h"
#include "SystemManager.h"
#include <utility>

constexpr unsigned int TOTAL_PLAYER = 1;
constexpr unsigned int TOTAL_PROJECTILES = 50;
constexpr unsigned int TOTAL_ENEMIES = 20;

std::unordered_map<EntityName, std::array<ComponentType, TotalComponents>> assignEntityFactory()
{
	std::array<ComponentType, TotalComponents> projectileComponents{ ComponentType::Position, ComponentType::Drawable, ComponentType::Movable};
	std::array<ComponentType, TotalComponents> playerComponents{ ComponentType::Drawable, ComponentType::Position, ComponentType::Movable };
	std::array<ComponentType, TotalComponents> enemyComponents{ ComponentType::Drawable, ComponentType::Position, ComponentType::Movable };

	std::unordered_map<EntityName, std::array<ComponentType, TotalComponents>> entityComponents;
	entityComponents.emplace(EntityName::Projectile, std::move(projectileComponents));
	entityComponents.emplace(EntityName::Player, std::move(playerComponents));
	entityComponents.emplace(EntityName::Enemy, std::move(enemyComponents));

	return entityComponents;
}

//Entity Pool
EntityManager::EntityFactory::EntityFactory()
	: m_entityFactory(assignEntityFactory()),
	m_entityPool()
{
	m_entityPool.reserve(MAX_ENTITIES);

	//Load in projectiles
	for (int i = 0; i < TOTAL_PROJECTILES; ++i)
	{
		createEntity(EntityName::Projectile);
	}

	//load in player(s)
	for (int i = 0; i < TOTAL_PLAYER; ++i)
	{
		createEntity(EntityName::Player);
	}

	//load in enemies
	for (int i = 0; i < TOTAL_ENEMIES; ++i)
	{
		createEntity(EntityName::Enemy);
	}
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

const std::array<ComponentType, TotalComponents>& EntityManager::EntityFactory::getEntityComponents(EntityName name) const
{
	auto iter = m_entityFactory.find(name);
	assert(iter != m_entityFactory.cend());
	return iter->second;
}

void EntityManager::EntityFactory::createEntity(EntityName name)
{
	const Entity entity(name, m_entityCount);
	SystemManager::getInstance().assignEntityToComponents(getEntityComponents(entity.m_name), entity.m_ID);
	m_entityPool.push_back(entity);
	++m_entityCount;
}

//EntityManager
EntityManager::EntityManager()
{
}

void EntityManager::addEntity(EntityName name)
{
	Entity* entity = m_entityFactory.getEntity(name);
	assert(entity);
	entity->m_inUse = true;
	//Assign entity starting position here

	m_entities.push_back(entity);
}
  
void EntityManager::removeEntity(int entityID)
{
	auto entity = std::find_if(m_entities.begin(), m_entities.end(), [entityID] (const auto& entity) { return entity->m_ID == entityID; });
	assert(entity != m_entities.cend());
	(*entity)->m_inUse = false;
	//reset entity position

	m_entities.erase(entity);
}