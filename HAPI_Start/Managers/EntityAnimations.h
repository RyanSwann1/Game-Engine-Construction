#pragma once

#include "../Animation/AnimationDetails.h"
#include <unordered_map>
#include <string>
#include <vector>

class EntityAnimations
{
public:
	static EntityAnimations& getInstance()
	{
		static EntityAnimations instance;
		return instance;
	}
	EntityAnimations(const EntityAnimations&) = delete;
	EntityAnimations& operator=(const EntityAnimations&) = delete;
	EntityAnimations(EntityAnimations&&) = delete;
	EntityAnimations&& operator=(EntityAnimations&&) = delete;

	const std::vector<AnimationDetails>& getAllEntityAnimations(EntityName entityName) const;
	const AnimationDetails& getEntityAnimationDetails(EntityName entityName, AnimationName animationName) const;

private:
	EntityAnimations();
	const std::unordered_map<EntityName, std::vector<AnimationDetails>> m_entityAnimations;
};