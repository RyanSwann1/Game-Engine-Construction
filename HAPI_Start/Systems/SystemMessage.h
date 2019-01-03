#pragma once

#include "SystemAction.h"
#include "SystemType.h"

class Entity;
class SystemMessage
{
public:
	SystemMessage(const Entity& entity, SystemAction action, SystemType destination)
		: m_entity(entity),
		m_action(action),
		m_destination(destination)
	{}

	const Entity& m_entity;
	const SystemAction m_action;
	const SystemType m_destination;
};