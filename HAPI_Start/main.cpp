#include <array>
#include <vector>
#include <memory>
#include "Utilities.h"
#include "Window.h"
#include "Sprite.h"
#include "Managers/TextureManager.h"
#include "Managers/StateManager.h"
#include "Managers/EntityManager.h"
#include "Components/ComponentPosition.h"
#include "Managers/SystemManager.h"
#include <iostream>
#include "Allocate.h"

//Source space == Texture
//Destinatipon Space == Screen

using namespace HAPISPACE;

void gameLoop(Sprite& playerSprite, Window& window, int spriteMovementSpeed);
void handleSpriteMovement(Sprite& playerSprite, Vector2i windowSize, int spriteMovementSpeed);
float getDeltaTime(DWORD lastFrameStart, DWORD frameStart);

//https://www.youtube.com/watch?v=0MdSJsCTRkY

void HAPI_Main()
{
	Window* window = Window::create("HAPI_WINDOW", Vector2i(1028, 720));
	if (!window)
	{
		Utilities::displayErrorMessage("Failed to initialize HAPI.");
		return;
	}

	//TextureManager textureManager;
	//textureManager.loadTexture("playerSprite.tga");
	//Sprite playerSprite("playerSprite.tga", textureManager, Vector2i(150, 150), Vector2i(100, 100));


	//std::cout << "MAKE UNIQUE\n";
	//std::vector<std::unique_ptr<Test>> tests;
	//tests.emplace_back(std::make_unique<Test>());
	//tests.emplace_back(std::make_unique<Test>());
	//tests.emplace_back(std::make_unique<Test>());
	//tests.emplace_back(std::make_unique<Test>());
	//tests.emplace_back(std::make_unique<Test>());
	//tests.emplace_back(std::make_unique<Test>());
	//tests.emplace_back(std::make_unique<Test>());
	//tests.emplace_back(std::make_unique<Test>());
	//tests.emplace_back(std::make_unique<Test>());
	//tests.emplace_back(std::make_unique<Test>());
	//tests.emplace_back(std::make_unique<Test>());
	//tests.emplace_back(std::make_unique<Test>());
	//for (const auto& test : tests)
	//{
	//	std::cout << &test << "\n";
	//}

	EntityManager entityManager;

	auto& m = SystemManager::getInstance();

	int i = 0;

	delete window;
}

void gameLoop(Sprite& playerSprite, Window & window, int spriteMovementSpeed)
{
	auto lastFrameStart = HAPI.GetTime();
	while (HAPI.Update())
	{
		const auto frameStart = HAPI.GetTime(); 
		
		window.clearScreenToBlack();

		handleSpriteMovement(playerSprite, window.getSize(), spriteMovementSpeed);

		window.blit(playerSprite);

		lastFrameStart = frameStart;
	}
}

float getDeltaTime(DWORD lastFrameStart, DWORD frameStart)
{
	return static_cast<float>(frameStart - lastFrameStart) / 1000.f;
}

void handleSpriteMovement(Sprite & playerSprite, Vector2i windowSize, int spriteMovementSpeed)
{
	Vector2i moveAmount;
	const auto currentEvent = HAPI.GetKeyboardData();
	if (currentEvent.scanCode[HK_UP])
	{
		playerSprite.moveBy(windowSize, Vector2i(0, -spriteMovementSpeed));
	}
	else if (currentEvent.scanCode[HK_DOWN])
	{
		playerSprite.moveBy(windowSize, Vector2i(0, spriteMovementSpeed));
	}
	else if (currentEvent.scanCode[HK_LEFT])
	{
		playerSprite.moveBy(windowSize, Vector2i(-spriteMovementSpeed, 0));
	}
	else if (currentEvent.scanCode[HK_RIGHT])
	{
		playerSprite.moveBy(windowSize, Vector2i(spriteMovementSpeed, 0));
	}
}