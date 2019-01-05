#pragma once

#include "ComponentType.h"
#include "../Sprite.h"

class ComponentDrawable
{
public:
	ComponentDrawable();

	int m_owningEntityID;
	Sprite m_sprite;
};
