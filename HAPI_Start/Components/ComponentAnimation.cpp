#include "ComponentAnimation.h"
#include "../Managers/EntityManager.h"

ComponentAnimation::ComponentAnimation()
	: m_owningEntityID(ENTITY_ID_NULL),
	m_animationPlayer()
{}