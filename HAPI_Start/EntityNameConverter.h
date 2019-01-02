#pragma once

#include "NameConverter.h"
#include "EntityName.h"

class EntityNameConverter : public NameConverter<EntityName>
{
public:
	static EntityNameConverter& getInstance()
	{
		static EntityNameConverter instance;
		return instance;
	}

private:
	EntityNameConverter();
};