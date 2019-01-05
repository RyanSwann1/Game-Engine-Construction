#include "ComponentDrawable.h"
#include "../Managers/EntityManager.h"
#include "ComponentPosition.h"

ComponentPosition::ComponentPosition()
	: m_owningEntityID(ENTITY_ID_NULL),
	m_position(),
	m_oldPosition()
{}