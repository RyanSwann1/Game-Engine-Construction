#pragma once

#include "ComponentType.h"
#include "../Animation/AnimationPlayer.h"

class ComponentAnimation
{
public:
	ComponentAnimation(ComponentType type);

	const ComponentType m_type;
	int m_owningEntityID;
	AnimationPlayer m_animationPlayer;
};