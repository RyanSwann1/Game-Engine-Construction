#pragma once

#include "../EntityName.h"
#include "AnimationName.h"
#include "../MoveDirection.h"
#include "../Vector2i.h"
#include <string>

class AnimationDetails
{
public:
	AnimationDetails(EntityName entityName, AnimationName name, std::string&& textureName,
		std::string&& direction, int startID, int endID, float frameTime, bool repeatable, bool reversible, Vector2i drawLocationSize);

	const EntityName m_entityName;
	const AnimationName m_name;
	const std::string m_textureName;
	const std::string m_direction;
	const int m_startFrame;
	const int m_endFrame;
	const float m_frameTime;
	const bool m_repeatable;
	const bool m_reversible;
	const Vector2i m_drawLocationSize;
};