#pragma once

#include "ComponentType.h"
#include "../MoveDirection.h"
#include "../Vector2i.h"

class ComponentMovable
{
public:
	ComponentMovable(ComponentType type);

	const ComponentType m_type;
	int m_owningEntityID;
	MoveDirection m_moveDirection;
	Vector2i m_speed;
};