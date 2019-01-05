#pragma once

#include "ComponentType.h"
#include "../MoveDirection.h"
#include "../Vector2i.h"

class ComponentMovable
{
public:
	ComponentMovable();

	int m_owningEntityID;
	MoveDirection m_moveDirection;
	Vector2i m_speed;
};