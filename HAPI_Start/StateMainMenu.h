#pragma once

#include "StateBase.h"

class StateMainMenu : public StateBase
{
public:
	StateMainMenu(StateManager& stateManager, StateType type);
	StateMainMenu(const StateMainMenu&) = delete;
	StateMainMenu& operator=(const StateMainMenu&) = delete;
	StateMainMenu(StateMainMenu&&) = delete;
	StateMainMenu&& operator=(StateMainMenu&&) = delete;

	void update() override;
	void draw() const override;


};