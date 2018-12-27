#pragma once

#include "ComponentType.h"

class ComponentMovable
{
public:
	ComponentMovable(ComponentType type);

	const ComponentType m_type;
	int m_owningEntityID;
};