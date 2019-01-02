#include "ComponentAnimation.h"
#include "../Managers/EntityManager.h"

ComponentAnimation::ComponentAnimation(ComponentType type)
	: m_type(type),
	m_owningEntityID(ENTITY_NOT_IN_USE),
	m_animationPlayer()
{}