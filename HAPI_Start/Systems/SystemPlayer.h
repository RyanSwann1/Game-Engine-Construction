#pragma once

#include "SystemBase.h"

class SystemPlayer : public SystemBase
{
public:
	SystemPlayer();
	~SystemPlayer() override;
	SystemPlayer(const SystemPlayer&) = delete;
	SystemPlayer& operator=(const SystemPlayer&) = delete;
	SystemPlayer(SystemPlayer&&) = delete;
	SystemPlayer&& operator=(SystemPlayer&&) = delete;

	void update(float deltaTime) const override {}

private:
	void playerMoveLeft() const;
	void playerMoveRight() const;
	void playerMoveUp() const;
	void playerMoveDown() const;
};