#include "EntityAnimations.h"
#include "../Utilities.h"
#include "../Vector2i.h"
#include "../AnimationNameConverter.h"
#include "../EntityNameConverter.h"
#include <fstream>
#include <assert.h>
#include <sstream>
#include <algorithm>

std::unordered_map<EntityName, std::vector<AnimationDetails>> initializeAnimations()
{
	std::ifstream file(Utilities::getDataDirectory() + "Animations.txt");
	assert(file.is_open());
	std::string line;
	std::unordered_map<EntityName, std::vector<AnimationDetails>> entityAnimations;

	while (std::getline(file, line))
	{
		std::stringstream keyStream(line);
		if (line[0] == '|')
		{
			continue;
		}
		std::string entityName, textureName, animationName, direction;
		int startID = 0, endID = 0;
		float frameTime = 0;
		bool repeatable, reversible;
		Vector2i drawLocationSize;

		keyStream >> entityName >> textureName >> animationName >> direction >> startID >> endID >> frameTime
			>> repeatable >> drawLocationSize.m_x >> drawLocationSize.m_y >> reversible;

		//Convert data
		const EntityName convertedEntityName = EntityNameConverter::getInstance().getConvertedName(entityName);
		const AnimationName convertedAnimationName = AnimationNameConverter::getInstance().getConvertedName(animationName);

		auto iter = entityAnimations.find(convertedEntityName);
		//If entity animations already exist
		if (iter != entityAnimations.cend())
		{
			iter->second.emplace_back(convertedEntityName, convertedAnimationName, std::move(textureName),
				std::move(direction), startID, endID, frameTime, repeatable, reversible, drawLocationSize);
		}
		//new entity animations
		else
		{
			std::vector<AnimationDetails> v{ AnimationDetails(convertedEntityName, convertedAnimationName, std::move(textureName),
				std::move(direction), startID, endID, frameTime, repeatable, reversible, drawLocationSize) };
			entityAnimations.emplace(convertedEntityName, std::move(v));
		}
	}
	
	assert(!entityAnimations.empty());
	return entityAnimations;
}

//Entity Animations
EntityAnimations::EntityAnimations()
	: m_entityAnimations(initializeAnimations())
{}

const std::vector<AnimationDetails>& EntityAnimations::getAllEntityAnimations(EntityName entityName) const
{
	auto iter = m_entityAnimations.find(entityName);
	assert(iter != m_entityAnimations.cend());
	return iter->second;
}

const AnimationDetails & EntityAnimations::getEntityAnimationDetails(EntityName entityName, AnimationName animationName) const
{
	auto entityAnimations = m_entityAnimations.find(entityName);
	assert(entityAnimations != m_entityAnimations.cend());
	auto animation = std::find_if(entityAnimations->second.cbegin(), entityAnimations->second.cend(), [animationName](const auto& animation)
	{ return animation.m_name == animationName; });
	assert(animation != entityAnimations->second.cend());
	return (*animation);
}