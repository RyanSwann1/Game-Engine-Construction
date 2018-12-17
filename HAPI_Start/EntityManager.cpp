#include "EntityManager.h"
#include "ComponentPosition.h"
#include "ComponentDrawable.h"

//ComponentFactory
EntityManager::ComponentFactory::ComponentFactory()
{
	registerComponent<ComponentPosition>(ComponentType::Position);
	registerComponent<ComponentDrawable>(ComponentType::Drawable);
}

std::unique_ptr<ComponentBase> EntityManager::ComponentFactory::getComponent(ComponentType type) const
{
	auto iter = m_componentFactory.find(type);
	assert(iter != m_componentFactory.cend());
	return iter->second();
}

//EntityFactory
EntityManager::EntityFactory::EntityFactory()
{

}

EntityManager::EntityManager()
{
}

void EntityManager::update()
{
}
