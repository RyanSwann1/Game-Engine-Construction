#include "Game.h"
#include "Managers/InputManager.h"
#include "Managers/TextureManager.h"

Game::Game(Vector2i windowSize)
	: m_window(windowSize),
	m_stateManager(),
	m_gameIsRunning(true)
{
	TextureManager::getInstance().loadTexture("playerSprite.tga");

	m_stateManager.switchToState(StateType::Game);
	
}

bool Game::isRunning() const
{
	return m_gameIsRunning;
}

void Game::update()
{
	HAPI.Update();
	m_stateManager.update();
	InputManager::getInstance().update();
}

void Game::draw()
{
	m_stateManager.draw(m_window);
}

void Game::lateUpdate()
{
	//void gameLoop(Sprite& playerSprite, Window & window, int spriteMovementSpeed)
	//{
	//	auto lastFrameStart = HAPI.GetTime();
	//	while (HAPI.Update())
	//	{
	//		//inputManager.registerBind('v');
	//		const auto frameStart = HAPI.GetTime(); 
	//		
	//		window.clearScreenToBlack();
	//
	//		handleSpriteMovement(playerSprite, window.getSize(), spriteMovementSpeed);
	//
	//		window.blit(playerSprite);
	//
	//		lastFrameStart = frameStart;
	//	}
	//}
}

float Game::getDeltaTime(DWORD lastFrameStart, DWORD frameStart) const
{
	return static_cast<float>(frameStart - lastFrameStart) / 1000.f;
}
