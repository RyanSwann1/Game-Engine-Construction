#include "AnimationDetails.h"

AnimationDetails::AnimationDetails(EntityName entityName, AnimationName name, std::string && textureName, std::string&& direction, 
	int startID, int endID, float frameTime, bool repeatable, bool reversible, Vector2i drawLocationSize)
	: m_entityName(entityName),
	m_name(name),
	m_textureName(std::move(textureName)),
	m_direction(std::move(direction)),
	m_startID(startID),
	m_endID(endID),
	m_frameTime(frameTime),
	m_repeatable(repeatable),
	m_reversible(reversible),
	m_drawLocationSize(drawLocationSize)
{}