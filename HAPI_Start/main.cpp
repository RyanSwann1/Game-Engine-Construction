#include <array>
#include <vector>
#include <memory>
#include "Utilities.h"
#include "Window.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "StateManager.h"


//Source space == Texture
//Destinatipon Space == Screen

using namespace HAPISPACE;

void gameLoop(Sprite& playerSprite, Window& window, int spriteMovementSpeed);
void handleSpriteMovement(Sprite& playerSprite, Vector2i windowSize, int spriteMovementSpeed);
float getDeltaTime(DWORD lastFrameStart, DWORD frameStart);

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
	const int spriteMovementSpeed = 3;
	StateManager stateManager;
	stateManager.switchToState(StateType::MainMenu);
	stateManager.switchToState(StateType::Game);
	
	int i = 0;
	stateManager.removeState(StateType::Game);
	stateManager.removeState(StateType::MainMenu);
	stateManager.update();
	int x = 0;
	//gameLoop(playerSprite, *window, spriteMovementSpeed);

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
