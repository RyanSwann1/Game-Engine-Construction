#pragma once

#include "SystemBase.h"

class Window;
class SystemAnimation : public SystemBase
{
public:
	SystemAnimation() {}
	SystemAnimation(const SystemAnimation&) = delete;
	SystemAnimation& operator=(const SystemAnimation&) = delete;
	SystemAnimation(SystemAnimation&&) = delete;
	SystemAnimation&& operator=(SystemAnimation&&) = delete;

	void update(float deltaTime) const override;
};