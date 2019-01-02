#pragma once

#include "NameConverter.h"
#include "Animation/AnimationName.h"

class AnimationNameConverter : public NameConverter<AnimationName>
{
public:
	static AnimationNameConverter& getInstance()
	{
		static AnimationNameConverter instance;
		return instance;
	}
private:
	AnimationNameConverter();
};