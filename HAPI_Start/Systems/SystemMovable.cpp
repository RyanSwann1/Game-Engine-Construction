#include "SystemMovable.h"
#include "../Managers/SystemManager.h"
#include "../Managers/EntityManager.h"
#include "../Entity.h"
#include "../Components/ComponentMovable.h"
#include "SystemMessage.h"

void SystemMovable::update(float deltaTime) const
{
	for (const auto& componentMovable : SystemManager::getInstance().getAllMovableComponents())
	{
		if (componentMovable.m_owningEntityID == ENTITY_ID_NULL)
		{
			continue;
		}

		Vector2i entitySpeed = componentMovable.m_speed;
		switch (componentMovable.m_moveDirection)
		{
		case MoveDirection::Left:
		{
			moveEntity(componentMovable.m_owningEntityID, Vector2i(-entitySpeed.m_x, 0));
			break;
		} 
		case MoveDirection::Right:
		{
			moveEntity(componentMovable.m_owningEntityID, Vector2i(entitySpeed.m_x, 0));
			break;
		}
		case MoveDirection::Up:
		{
			moveEntity(componentMovable.m_owningEntityID, Vector2i(0, -entitySpeed.m_y));
			break;
		}
		case MoveDirection::Down:
		{
			moveEntity(componentMovable.m_owningEntityID, Vector2i(0, entitySpeed.m_y));
			break;
		}
		}
	}
}

void SystemMovable::onSystemMessage(const SystemMessage& message) const
{
	auto& entityMoveDirection = SystemManager::getInstance().getMovableComponent(message.m_entityID).m_moveDirection;
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
	auto& componentPosition = SystemManager::getInstance().getPositionComponent(entityID);
	componentPosition.m_position += moveBy;
} 