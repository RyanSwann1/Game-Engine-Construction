#pragma once

#include "SystemType.h"

template <class T>
class SystemSpecializedMessage;
class SystemMessage;
class Entity;
class Vector2i;
class SystemBase
{
public:
	SystemBase() {}
	virtual ~SystemBase() {}
	SystemBase(const SystemBase&) = delete;
	SystemBase& operator=(const SystemBase&) = delete;
	SystemBase(SystemBase&&) = delete;
	SystemBase&& operator=(SystemBase&&) = delete;
	
	virtual void update(float deltaTime) const = 0;
	virtual void onSystemMessage(const SystemMessage& message) const {}
	virtual void onSystemSpecializedMessage(const SystemSpecializedMessage<Vector2i>& message) const {}

};