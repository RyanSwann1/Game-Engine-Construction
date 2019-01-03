#include "StateGame.h"
#include "../Managers/SystemManager.h"

StateGame::StateGame(StateManager & stateManager, StateType type)
	: StateBase(stateManager, type)
{
	m_entityManager.addEntity(EntityName::Player, Vector2i(50, 50));
}

void StateGame::update()
{
	m_entityManager.update();
	SystemManager::getInstance().update(m_entityManager.getEntities());
}

void StateGame::draw(const Window & window) const
{
	SystemManager::getInstance().draw(window);
}
