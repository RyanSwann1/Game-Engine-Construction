#pragma once
#include "SystemBase.h"

class Window;
class SystemDrawable :
	public SystemBase
{
public:
	SystemDrawable() {}
	SystemDrawable(const SystemDrawable&) = delete;
	SystemDrawable& operator=(const SystemDrawable&) = delete;
	SystemDrawable(SystemDrawable&&) = delete;
	SystemDrawable&& operator=(SystemDrawable&&) = delete;

	void update(float deltaTime) const override {}
	void draw(const Window& window) const;
	void onSystemMessage(const SystemMessage& message) const override;
};