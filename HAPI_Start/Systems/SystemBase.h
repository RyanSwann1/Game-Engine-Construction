#pragma once

#include "SystemType.h"
#include "SystemMessage.h"
#include <vector>
#include <iostream>

class Entity;
class SystemBase
{
public:
	SystemBase(SystemType type);
	virtual ~SystemBase() {}
	SystemBase(const SystemBase&) = delete;
	SystemBase& operator=(const SystemBase&) = delete;
	SystemBase(SystemBase&&) = delete;
	SystemBase&& operator=(SystemBase&&) = delete;
	
	virtual void update(const std::vector<Entity*>& entities) const = 0;
	virtual void onSystemMessage(const SystemMessage& message) const {}

protected:
	template <class Component>
	bool isComponentInUse(const Component& component) const
	{
		return static_cast<Component>(component).m_owningEntityID != -1;
	}

private:
	const SystemType m_type;
};