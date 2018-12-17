#include "ComponentBase.h"

ComponentBase::ComponentBase(ComponentType type)
	: m_type(type)
{
}

ComponentType ComponentBase::getType() const
{
	return m_type;
}
