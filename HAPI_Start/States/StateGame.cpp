#include "StateGame.h"
#include "../Managers/SystemManager.h"

StateGame::StateGame(StateManager & stateManager, StateType type)
	: StateBase(stateManager, type)
{
}

void StateGame::update()
{
	m_entityManager.update();
}

void StateGame::draw(const Window & window) const
{
	SystemManager::getInstance().draw(window);
}
