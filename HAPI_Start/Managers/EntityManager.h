#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include <functional>
#include <string>
#include <assert.h>
#include <array>
#include "../Entity.h"
#include "../Components/ComponentType.h"
#include "../Vector2i.h"

constexpr size_t MAX_ENTITIES = 100;
constexpr int ENTITY_ID_NULL = -1;
constexpr int PLAYER_ID = 0;

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
		const std::unordered_map<EntityName, std::vector<ComponentType>> m_entityFactory;
		std::vector<Entity> m_entityPool;
		int m_entityCount;

		const std::vector<ComponentType>& getEntityComponents(EntityName name) const;
		void createEntity(EntityName name);
	};

public:
	EntityManager();
	EntityManager(const EntityManager&) = delete;
	EntityManager& operator=(const EntityManager&) = delete;
	EntityManager(EntityManager&&) = delete;
	EntityManager&& operator=(EntityManager&&) = delete;

	const Entity& getEntity(int entityID) const;
	const std::vector<Entity*>& getEntities() const;

	void addEntity(EntityName name, Vector2i startingPosition);
	void removeEntity(int entityID);
	void update();

private:
	EntityFactory m_entityFactory;
	std::vector<std::pair<EntityName, Vector2i>> m_entitiesToAdd;
	std::vector<Entity*> m_entities;
	std::vector<int> m_entitiesToRemove;
	
	void handleEntityRemovals();
	void handleEntityAdditions();
};