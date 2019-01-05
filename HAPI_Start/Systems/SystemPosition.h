#pragma once

#include "SystemBase.h"

class SystemPosition : public SystemBase
{
public:
	SystemPosition();
	SystemPosition(const SystemPosition&) = delete;
	SystemPosition& operator=(const SystemPosition&) = delete;
	SystemPosition(SystemPosition&&) = delete;
	SystemPosition&& operator=(SystemPosition&&) = delete;

	void update(float deltaTime) const override {}
	void onSystemSpecializedMessagePosition(const SystemSpecializedMessage<Vector2i>& message) const override;
};