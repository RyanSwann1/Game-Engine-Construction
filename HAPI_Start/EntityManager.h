#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include <assert.h>
#include <functional>
#include "Entity.h"
#include "ComponentBase.h"

class EntityManager
{
	class ComponentFactory
	{
	public:
		ComponentFactory();
		ComponentFactory(const ComponentFactory&) = delete;
		ComponentFactory& operator=(const ComponentFactory&) = delete;
		ComponentFactory(ComponentFactory&&) = delete;
		ComponentFactory&& operator=(ComponentFactory&&) = delete;

		std::unique_ptr<ComponentBase> getComponent(ComponentType type) const;

	private:
		std::unordered_map<ComponentType, std::function<std::unique_ptr<ComponentBase>()>> m_componentFactory;

		template <class Component>
		void registerComponent(ComponentType type)
		{
			assert(m_componentFactory.find(type) == m_componentFactory.cend());
			m_componentFactory.emplace(type, [type]() -> std::unique_ptr<Component>
			{
				return std::make_unique<Component>(type);
			});
		}
	};

	class EntityFactory
	{
	public:
		EntityFactory();
		EntityFactory(const EntityFactory&) = delete;
		EntityFactory& operator=(const EntityFactory&) = delete;
		EntityFactory(EntityFactory&&) = delete;
		EntityFactory&& operator=(EntityFactory&&) = delete;


	private:

	};

	//Object Pooling
public:
	EntityManager();
	EntityManager(const EntityManager&) = delete;
	EntityManager& operator=(const EntityManager&) = delete;
	EntityManager(EntityManager&&) = delete;
	EntityManager&& operator=(EntityManager&&) = delete;

	void update();


private:
	const ComponentFactory m_componentFactory;
	const EntityFactory m_entityFactory;
	std::vector<Entity> m_entites;
};