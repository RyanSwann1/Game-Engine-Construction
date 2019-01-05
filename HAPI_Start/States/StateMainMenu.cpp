#include "StateMainMenu.h"

StateMainMenu::StateMainMenu(StateManager & stateManager)
	: StateBase(stateManager, StateType::MainMenu)
{}

void StateMainMenu::update(float deltaTime)
{
	//Enter game
	//Switch to state game
}

void StateMainMenu::draw(const Window& window) const
{
}
