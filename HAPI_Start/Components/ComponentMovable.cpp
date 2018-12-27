#include "ComponentMovable.h"
#include "../Managers/EntityManager.h"

ComponentMovable::ComponentMovable(ComponentType type)
	: m_type(type),
	m_owningEntityID(ENTITY_NOT_IN_USE)
{}