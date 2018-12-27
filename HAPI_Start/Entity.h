#pragma once


#include "EntityName.h"
#include <array>

class Entity
{
public:
	Entity(EntityName name, int ID)
		: m_ID(ID),
		m_name(name)
	{}
	
	const int m_ID;
	const EntityName m_name;
	bool m_inUse;
};