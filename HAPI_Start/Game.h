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
	bool m_gameIsRunning;

	float getDeltaTime(DWORD lastFrameStart, DWORD frameStart) const;
};

