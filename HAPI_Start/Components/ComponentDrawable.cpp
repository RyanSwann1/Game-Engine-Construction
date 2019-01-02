#include "ComponentDrawable.h"
#include "../Managers/EntityManager.h"

ComponentDrawable::ComponentDrawable(ComponentType type)
	: m_type(type),
	m_owningEntityID(ENTITY_NOT_IN_USE),
	m_sprite()
{}