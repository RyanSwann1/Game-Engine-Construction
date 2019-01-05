#pragma once

#include "StateBase.h"

class StateMainMenu : public StateBase
{
public:
	StateMainMenu(StateManager& stateManager);
	StateMainMenu(const StateMainMenu&) = delete;
	StateMainMenu& operator=(const StateMainMenu&) = delete;
	StateMainMenu(StateMainMenu&&) = delete;
	StateMainMenu&& operator=(StateMainMenu&&) = delete;

	void update(float deltaTime) override;
	void draw(const Window& window) const override;


};