#pragma once

#include "SystemAction.h"
#include "SystemType.h"
#include "../EntityName.h"

class SystemMessage
{
public:
	SystemMessage(int entityID, EntityName entityName, SystemAction action, SystemType destination)
		: m_entityID(entityID),
		m_entityName(entityName),
		m_action(action),
		m_destination(destination)
	{}
	SystemMessage(const SystemMessage&) = delete;
	SystemMessage& operator=(const SystemMessage&) = delete;
	SystemMessage(SystemMessage&&) = delete;
	SystemMessage&& operator=(SystemMessage&&) = delete;

	const int m_entityID;
	const EntityName m_entityName;
	const SystemAction m_action;
	const SystemType m_destination;
};