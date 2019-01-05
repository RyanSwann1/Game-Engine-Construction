#include "StateGame.h"
#include "../Managers/SystemManager.h"

StateGame::StateGame(StateManager & stateManager)
	: StateBase(stateManager, StateType::Game)
{
	m_entityManager.addEntity(EntityName::Player, Vector2i(100, 100));
}


void StateGame::update(float deltaTime)
{
	m_entityManager.update();
	SystemManager::getInstance().update(deltaTime);
}

void StateGame::draw(const Window & window) const
{
	SystemManager::getInstance().draw(window);
}