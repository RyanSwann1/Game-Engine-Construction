#pragma once

#include "SystemBase.h"

class SystemPlayer : public SystemBase
{
public:
	SystemPlayer(SystemType type);
	~SystemPlayer() override;
	SystemPlayer(const SystemPlayer&) = delete;
	SystemPlayer& operator=(const SystemPlayer&) = delete;
	SystemPlayer(SystemPlayer&&) = delete;
	SystemPlayer&& operator=(SystemPlayer&&) = delete;

	void update(const std::vector<Entity*>& entities) const override {}

private:
	void playerMoveLeft() const;
	void playerMoveRight() const;
	void playerMoveUp() const;
	void playerMoveDown() const;
};