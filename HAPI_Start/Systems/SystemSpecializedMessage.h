#pragma once

#include "SystemAction.h"
#include "SystemType.h"

class Entity;
template <class Message>
class SystemSpecializedMessage
{
public:
	SystemSpecializedMessage(const Entity& entity, Message message, SystemAction systemAction, SystemType messageDestination)
		: m_entity(entity),
		m_message(message),
		m_action(systemAction),
		m_destination(messageDestination)
	{}

	const Entity& m_entity;
	const Message m_message;
	const SystemAction m_action;
	const SystemType m_destination;
};