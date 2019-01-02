#include "Game.h"

//https://www.youtube.com/watch?v=0MdSJsCTRkY

void HAPI_Main()
{
	Vector2i windowSize(480, 640);
	if (!HAPI.Initialise(windowSize.m_x, windowSize.m_y, "HAPI_WINDOW"))
	{
		//Utilities::displayErrorMessage("Error");
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