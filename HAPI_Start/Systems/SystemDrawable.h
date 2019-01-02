#pragma once
#include "SystemBase.h"

class Window;
class SystemDrawable :
	public SystemBase
{
public:
	SystemDrawable(SystemType type);
	SystemDrawable(const SystemDrawable&) = delete;
	SystemDrawable& operator=(const SystemDrawable&) = delete;
	SystemDrawable(SystemDrawable&&) = delete;
	SystemDrawable&& operator=(SystemDrawable&&) = delete;

	void update(const std::vector<Entity*>& entities) const override {}
	void draw(const Window& window) const;
};