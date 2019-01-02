#pragma once

#include "EntityName.h"

class Entity
{
public:
	Entity(EntityName name, int ID)
		: m_ID(ID),
		m_name(name),
		m_inUse(false)
	{}
	
	const int m_ID;
	const EntityName m_name;
	bool m_inUse;
};