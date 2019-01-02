#pragma once


#include "StateBase.h"
#include "../Managers/EntityManager.h"

class StateGame : public StateBase
{
public:
	StateGame(StateManager& stateManager, StateType type);
	StateGame(const StateGame&) = delete;
	StateGame& operator=(const StateGame&) = delete;
	StateGame(StateGame&&) = delete;
	StateGame&& operator=(StateGame&&) = delete;

	void update() override;
	void draw(const Window& window) const override;

private:
	EntityManager m_entityManager;

};