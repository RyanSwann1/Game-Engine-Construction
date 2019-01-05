#include "ComponentMovable.h"
#include "../Managers/EntityManager.h"

ComponentMovable::ComponentMovable()
	: m_owningEntityID(ENTITY_ID_NULL),
	m_moveDirection(MoveDirection::None),
	m_speed()
{}