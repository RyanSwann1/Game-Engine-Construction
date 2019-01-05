#include "SystemPosition.h"
#include "SystemSpecializedMessage.h"
#include "../Managers/SystemManager.h"
#include "../Entity.h"

SystemPosition::SystemPosition()
{
}

void SystemPosition::onSystemSpecializedMessage(const SystemSpecializedMessage<Vector2i>& message) const
{
	switch (message.m_action)
	{
	case SystemAction::SetStartingPosition :
	{
		auto& componentPosition = SystemManager::getInstance().getComponentPosition(message.m_entity.m_ID);
		componentPosition.m_position = message.m_message;
		componentPosition.m_oldPosition = message.m_message;
		break;
	}
	}
}