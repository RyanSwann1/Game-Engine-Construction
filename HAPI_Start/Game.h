#pragma once

#include "Window.h"
#include "Managers/StateManager.h"

class Game
{
public:
	Game(Vector2i windowSize);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game&& operator=(Game&&) = delete;

	bool isRunning() const;
	void update();
	void draw();
	void lateUpdate();

private:
	Window m_window;
	StateManager m_stateManager;

	float getDeltaTime(DWORD lastFrameStart, DWORD frameStart) const
	{
		return static_cast<float>(frameStart - lastFrameStart) / 1000.f;
	}

	//
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

};

