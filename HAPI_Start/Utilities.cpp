#include "Utilities.h"
#include <random>
#include "HAPI_lib.h"
#include "Vector2i.h"
#include "EntityName.h"

std::string Utilities::getDataDirectory()
{
	return "data/";
}

int Utilities::getRandomNumber(int min, int max)
{
	static std::random_device rd;  
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max);

	return dis(gen);
}

void Utilities::displayFPSIndicator(Vector2i onScreenPosition)
{
	HAPI.SetShowFPS(true, onScreenPosition.m_x, onScreenPosition.m_y);
}

void Utilities::removeFPSIndicator()
{
	HAPI.SetShowFPS(false);
}

void Utilities::displayErrorMessage(const std::string & message)
{
	HAPI.UserMessage(message, "Error!");
}

std::string Utilities::convertEntityName(EntityName entityName)
{
	switch (entityName)
	{
	case EntityName::Player :
	{
		return std::string("Player");
		break;
	}
	case EntityName::Projectile :
	{
		return std::string("Projectile");
		break;
	}
	case EntityName::Enemy :
	{
		return std::string("Enemy");
		break;
	}
	}
}
