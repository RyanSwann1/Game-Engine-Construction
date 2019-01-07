#include "Game.h"

//https://www.youtube.com/watch?v=0MdSJsCTRkY

void HAPI_Main()
{
	Vector2i windowSize(1000, 1000);
	if (!HAPI.Initialise(windowSize.m_x, windowSize.m_y, "HAPI_WINDOW"))
	{
		return;
	}

	Game game(windowSize);
	while (game.isRunning())
	{
		game.update();
		game.draw();
		game.lateUpdate();
	}
}