#include "SystemPlayer.h"
#include "../Managers/EntityManager.h"
#include "../Managers/InputManager.h"
#include "../Managers/SystemManager.h"
#include "../Systems/SystemMessage.h"

SystemPlayer::SystemPlayer()
{
	InputManager::getInstance().registerBinding(std::bind(&SystemPlayer::playerMoveLeft, this), 
		KeyCommandName::PlayerMoveLeft, StateType::Game, KeyBind::LeftArrow);

	InputManager::getInstance().registerBinding(std::bind(&SystemPlayer::playerMoveRight, this),
		KeyCommandName::PlayerMoveRight, StateType::Game, KeyBind::RightArrow);

	InputManager::getInstance().registerBinding(std::bind(&SystemPlayer::playerMoveUp, this),
		KeyCommandName::PlayerMoveUp, StateType::Game, KeyBind::UpArrow);

	InputManager::getInstance().registerBinding(std::bind(&SystemPlayer::playerMoveDown, this),
		KeyCommandName::PlayerMoveDown, StateType::Game, KeyBind::DownArrow);
}

SystemPlayer::~SystemPlayer()
{
	InputManager::getInstance().unregisterBinding(KeyCommandName::PlayerMoveLeft);
	InputManager::getInstance().unregisterBinding(KeyCommandName::PlayerMoveRight);
	InputManager::getInstance().unregisterBinding(KeyCommandName::PlayerMoveUp);
	InputManager::getInstance().unregisterBinding(KeyCommandName::PlayerMoveDown);
}

void SystemPlayer::playerMoveLeft() const
{
	SystemManager::getInstance().sendSystemMessage(SystemMessage(PLAYER_ID, EntityName::Player, SystemAction::MoveEntityLeft, SystemType::Movable));
}

void SystemPlayer::playerMoveRight() const
{
	SystemManager::getInstance().sendSystemMessage(SystemMessage(PLAYER_ID, EntityName::Player, SystemAction::MoveEntityRight, SystemType::Movable));
}

void SystemPlayer::playerMoveUp() const
{
	SystemManager::getInstance().sendSystemMessage(SystemMessage(PLAYER_ID, EntityName::Player, SystemAction::MoveEntityUp, SystemType::Movable));
}

void SystemPlayer::playerMoveDown() const
{
	SystemManager::getInstance().sendSystemMessage(SystemMessage(PLAYER_ID, EntityName::Player, SystemAction::MoveEntityDown, SystemType::Movable));
}