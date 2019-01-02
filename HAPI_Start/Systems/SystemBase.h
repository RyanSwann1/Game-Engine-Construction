#pragma once

#include "SystemType.h"
#include "SystemMessage.h"
#include <vector>

class Entity;
class SystemBase
{
public:
	SystemBase(SystemType type)
		: m_type(type)
	{}
	virtual ~SystemBase() {}
	
	SystemBase(const SystemBase&) = delete;
	SystemBase& operator=(const SystemBase&) = delete;
	SystemBase(SystemBase&&) = delete;
	SystemBase&& operator=(SystemBase&&) = delete;
	
	virtual void update(const std::vector<Entity*>& entities) const = 0;
	virtual void onSystemMessage() const {}

private:
	const SystemType m_type;
};