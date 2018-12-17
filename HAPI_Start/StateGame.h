#pragma once


#include "StateBase.h"

class StateGame : public StateBase
{
public:
	StateGame(StateManager& stateManager, StateType type);
	StateGame(const StateGame&) = delete;
	StateGame& operator=(const StateGame&) = delete;
	StateGame(StateGame&&) = delete;
	StateGame&& operator=(StateGame&&) = delete;

	void update() override {}
	void draw() const override {};

private:

};