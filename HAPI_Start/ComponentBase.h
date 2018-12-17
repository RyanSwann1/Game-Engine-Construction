#pragma once

#include "ComponentType.h"

class ComponentBase
{
public:
	ComponentBase(ComponentType type);

	ComponentType getType() const;

private:
	const ComponentType m_type;
};