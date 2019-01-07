#include "Game.h"
#include "Managers/InputManager.h"
#include "Managers/TextureManager.h"

Game::Game(Vector2i windowSize)
	: m_window(windowSize),
	m_stateManager(),
	m_gameIsRunning(true),
	m_lastFrameStart(HAPI.GetTime()),
	m_frameStart(HAPI.GetTime()),
	m_deltaTime(0)
{
	TextureManager::getInstance().loadTexture("character.png");
	TextureManager::getInstance().loadTexture("Overworld.png");

	m_stateManager.switchToState(StateType::Game);
}

Game::~Game()
{
	TextureManager::getInstance().unloadTexture("character.png");
}

bool Game::isRunning() const
{
	return m_gameIsRunning;
}

void Game::update()
{
	m_frameStart = HAPI.GetTime();
	m_gameIsRunning = HAPI.Update();
	InputManager::getInstance().update();
	m_stateManager.update(m_deltaTime);
}

void Game::draw()
{
	m_stateManager.draw(m_window);
}

void Game::lateUpdate()
{
	m_deltaTime = getDeltaTime();
	m_lastFrameStart = m_frameStart;
}

float Game::getDeltaTime() const
{
	return static_cast<float>(m_frameStart - m_lastFrameStart) / 1000.f;
}