#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include <functional>
#include <string>
#include <assert.h>
#include "../Entity.h"
#include "../Components/ComponentType.h"

constexpr size_t MAX_ENTITIES = 100;
constexpr int ENTITY_NOT_IN_USE = -1;

class EntityManager
{
	class EntityFactory
	{
	public:
		EntityFactory();
		EntityFactory(const EntityFactory&) = delete;
		EntityFactory& operator=(const EntityFactory&) = delete;
		EntityFactory(EntityFactory&&) = delete;
		EntityFactory&& operator=(EntityFactory&&) = delete;

		Entity* getEntity(EntityName name);

	private:
		const std::unordered_map<EntityName, std::array<ComponentType, TotalComponents>> m_entityFactory;
		std::vector<Entity> m_entityPool;
		int m_entityCount;

		const std::array<ComponentType, TotalComponents>& getEntityComponents(EntityName name) const;
		void createEntity(EntityName name);
	};

public:
	EntityManager();
	EntityManager(const EntityManager&) = delete;
	EntityManager& operator=(const EntityManager&) = delete;
	EntityManager(EntityManager&&) = delete;
	EntityManager&& operator=(EntityManager&&) = delete;

	void addEntity(EntityName name);
	void removeEntity(int entityID);

private:
	EntityFactory m_entityFactory;
	std::vector<Entity*> m_entities;
};