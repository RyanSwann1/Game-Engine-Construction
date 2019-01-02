#pragma once

#include "ComponentType.h"
#include "../Sprite.h"

class ComponentDrawable
{
public:
	ComponentDrawable(ComponentType type);

	const ComponentType m_type;
	int m_owningEntityID;
	Sprite m_sprite;
};
