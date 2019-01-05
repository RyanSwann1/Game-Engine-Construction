#include "AnimationNameConverter.h"

std::unordered_map<std::string, AnimationName> initializeAnimationNames()
{
	std::unordered_map<std::string, AnimationName> animationNames;
	animationNames.reserve(static_cast<size_t>(AnimationName::Total));
	animationNames.emplace("WalkingUp", AnimationName::WalkingUp);
	animationNames.emplace("WalkingDown", AnimationName::WalkingDown);
	animationNames.emplace("WalkingLeft", AnimationName::WalkingLeft);
	animationNames.emplace("WalkingRight", AnimationName::WalkingRight);
	animationNames.emplace("Default", AnimationName::Default);

	return animationNames;
}

AnimationNameConverter::AnimationNameConverter()
	: NameConverter(initializeAnimationNames())
{}
