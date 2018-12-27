#include "ComponentDrawable.h"
#include "../Managers/EntityManager.h"
#include "ComponentPosition.h"

ComponentPosition::ComponentPosition(ComponentType type)
	: m_type(type),
	m_owningEntityID(ENTITY_NOT_IN_USE),
	m_position(),
	m_oldPosition()
{}