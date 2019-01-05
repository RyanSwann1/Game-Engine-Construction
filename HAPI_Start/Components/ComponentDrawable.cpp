#include "ComponentDrawable.h"
#include "../Managers/EntityManager.h"

ComponentDrawable::ComponentDrawable()
	: m_owningEntityID(ENTITY_ID_NULL),
	m_sprite()
{}