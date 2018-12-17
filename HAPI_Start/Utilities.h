#pragma once

#include <string>
struct Vector2i;
namespace Utilities
{
	std::string getDataDirectory();
	int getRandomNumber(int min, int max);
	void displayFPSIndicator(Vector2i onScreenPosition);
	void removeFPSIndicator();
	void displayErrorMessage(const std::string& message);
}