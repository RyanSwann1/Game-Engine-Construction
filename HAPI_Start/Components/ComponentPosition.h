#pragma once

#include "ComponentType.h"
#include "../Vector2i.h"

class ComponentPosition
{
public:
	ComponentPosition();

	int m_owningEntityID;
	Vector2i m_position;
	Vector2i m_oldPosition;
};