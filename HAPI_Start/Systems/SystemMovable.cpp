#include "SystemMovable.h"
#include "../Managers/SystemManager.h"
#include "../Entity.h"
#include "../Components/ComponentMovable.h"

SystemMovable::SystemMovable(SystemType type)
	: SystemBase(type)
{}

void SystemMovable::update(const std::vector<Entity*>& entities) const
{
	for (const auto& entity : entities)
	{
		const auto& componentMovable = SystemManager::getInstance().getComponentMovable(entity->m_ID);
		Vector2i entitySpeed = componentMovable.m_speed;
		switch (componentMovable.m_moveDirection)
		{
		case MoveDirection::Left :
		{
			moveEntity(entity->m_ID, Vector2i(-entitySpeed.m_x, 0));
			break;
		}
		case MoveDirection::Right :
		{
			moveEntity(entity->m_ID, Vector2i(entitySpeed.m_x, 0));
			break;
		}
		case MoveDirection::Up :
		{
			moveEntity(entity->m_ID, Vector2i(0, -entitySpeed.m_y));
			break;
		}
		case MoveDirection::Down :
		{
			moveEntity(entity->m_ID, Vector2i(0, entitySpeed.m_y));
			break;
		}
		}
	}
}

void SystemMovable::onSystemMessage(const SystemMessage& message) const
{
	auto& entityMoveDirection = SystemManager::getInstance().getComponentMovable(message.m_entity.m_ID).m_moveDirection;
	switch (message.m_action)
	{
	case SystemAction::MoveEntityLeft :
	{
		entityMoveDirection = MoveDirection::Left;
		break;
	}
	case SystemAction::MoveEntityRight :
	{
		entityMoveDirection = MoveDirection::Right;
		break;
	}
	case SystemAction::MoveEntityUp :
	{
		entityMoveDirection = MoveDirection::Up;
		break;
	}
	case SystemAction::MoveEntityDown :
	{
		entityMoveDirection = MoveDirection::Down;
		break;
	}
	}
}

void SystemMovable::moveEntity(int entityID, Vector2i moveBy) const
{
	auto& componentPosition = SystemManager::getInstance().getComponentPosition(entityID);
	componentPosition.m_position += moveBy;
} 