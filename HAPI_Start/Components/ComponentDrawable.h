#pragma once

#include "ComponentType.h"

class ComponentDrawable
{
public:
	ComponentDrawable(ComponentType type);

	const ComponentType m_type;
	int m_owningEntityID;
};
