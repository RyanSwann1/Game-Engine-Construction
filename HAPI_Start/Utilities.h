#pragma once

#include <string>
enum class EntityName;
struct Vector2i;
namespace Utilities
{
	std::string getDataDirectory();
	int getRandomNumber(int min, int max);
	void displayFPSIndicator(Vector2i onScreenPosition);
	void removeFPSIndicator();
	void displayErrorMessage(const std::string& message);
	std::string convertEntityName(EntityName entityName);
}