#include "Game.h"
#include "Managers/InputManager.h"

Game::Game(Vector2i windowSize)
	: m_window(windowSize)
{
	m_stateManager.switchToState(StateType::Game);
}

bool Game::isRunning() const
{
	return false;
}

void Game::update()
{
	while (HAPI.Update())
	{
		m_stateManager.update();
		InputManager::getInstance().update();
	}
}

void Game::draw()
{
	m_stateManager.draw(m_window);
}

void Game::lateUpdate()
{
}
