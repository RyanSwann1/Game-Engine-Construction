#pragma once

#include "SystemType.h"

class SystemBase
{
public:
	SystemBase(SystemType type)
		: m_type(type)
	{}
	
	SystemBase(const SystemBase&) = delete;
	SystemBase& operator=(const SystemBase&) = delete;
	SystemBase(SystemBase&&) = delete;
	SystemBase&& operator=(SystemBase&&) = delete;
	
private:
	const SystemType m_type;
};