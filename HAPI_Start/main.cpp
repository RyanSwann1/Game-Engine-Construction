#include "Game.h"

//https://www.youtube.com/watch?v=0MdSJsCTRkY

//void test();

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

//void test()
//{
//	int maxFrame = 4;
//	int currentFrame = 0;
//	const auto& playerAnimation = EntityAnimations::getInstance().getEntityAnimationDetails(EntityName::Player, AnimationName::Default);
//	Texture texture("character.PNG");
//	Sprite sprite;
//	sprite.setTexture(texture);
//	sprite.setRect(0, 32, 16, 32);
//
//	Window window(windowSize);
//
//	HAPISPACE::DWORD lastFrameStart = HAPI.GetTime();
//	HAPISPACE::DWORD frameStart = 0;
//	float deltaTime = 0;
//	Timer timer;
//
//	while (HAPI.Update())
//	{
//		frameStart = HAPI.GetTime();
//
//
//		if (timer.m_time > 500.f)
//		{
//			if (currentFrame == 0)
//			{
//				sprite.setRect(0, 32, 16, 32);
//				++currentFrame;
//			}
//			else if (currentFrame == 1)
//			{
//				sprite.setRect(16, 32, 16, 32);
//				++currentFrame;
//			}
//			else if (currentFrame == 2)
//			{
//				sprite.setRect(32, 32, 16, 32);
//				++currentFrame;
//			}
//			else if (currentFrame == 3)
//			{
//				sprite.setRect(48, 32, 16, 32);
//				currentFrame = 0;
//			}
//
//			timer.reset();
//		}
//
//
//
//		deltaTime = static_cast<float>(frameStart - lastFrameStart);
//		timer.update(deltaTime);
//		std::cout << timer.m_time << "\n";
//		lastFrameStart = frameStart;
//		window.draw(sprite, Vector2i(50, 50));
//
//	}
//
//}