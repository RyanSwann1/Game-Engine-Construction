#pragma once

#include "SystemBase.h"

class Window;
class SystemAnimation : public SystemBase
{
public:
	SystemAnimation(SystemType type);
	SystemAnimation(const SystemAnimation&) = delete;
	SystemAnimation& operator=(const SystemAnimation&) = delete;
	SystemAnimation(SystemAnimation&&) = delete;
	SystemAnimation&& operator=(SystemAnimation&&) = delete;

	void update(const std::vector<Entity*>& entities) const;
	void draw(const Window& window) const;
};