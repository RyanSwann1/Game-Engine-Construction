#pragma once

#include "../Animation/AnimationPlayer.h"

class ComponentAnimation
{
public:
	ComponentAnimation();

	
	int m_owningEntityID;
	AnimationPlayer m_animationPlayer;
};