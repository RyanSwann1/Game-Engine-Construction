#pragma once

#include "SystemBase.h"
#include "../Vector2i.h"

class SystemMovable : public SystemBase
{
public:
	SystemMovable() {}
	SystemMovable(const SystemMovable&) = delete;
	SystemMovable& operator=(const SystemMovable&) = delete;
	SystemMovable(SystemMovable&&) = delete;
	SystemMovable&& operator=(SystemMovable&&) = delete;

	void update(float deltaTime) const override;
	void onSystemMessage(const SystemMessage& message) const override;

private:
	void moveEntity(int entityID, Vector2i moveBy) const;
};