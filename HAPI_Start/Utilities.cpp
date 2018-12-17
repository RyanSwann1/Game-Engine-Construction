#include "Utilities.h"
#include <random>
#include "HAPI_lib.h"
#include "Vector2i.h"

std::string Utilities::getDataDirectory()
{
	return "data/";
}

int Utilities::getRandomNumber(int min, int max)
{
	static std::random_device rd;  //Will be used to obtain a seed for the random number engine
	static std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
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
