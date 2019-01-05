#pragma once

#include "../Sprite.h"
#include "AnimationName.h"
#include "../Timer.h"
#include <unordered_map>

enum class EntityName;
class AnimationDetails;
class Sprite;
class TileSheetDetails;
class AnimationPlayer
{
	enum class AnimationType
	{
		Horizontal = 0,
		Vertical
	};

	class Animation
	{
	public:
		Animation(const AnimationDetails& details, const TileSheetDetails& tileSheetDetails, AnimationType type);

		Vector2i getDrawLocationSize() const;
		const TileSheetDetails& getTileSheetDetails() const;

		void update(Rectangle& spriteRect, float deltaTime);

	private:
		const AnimationDetails& m_animationDetails;
		const TileSheetDetails& m_tileSheetDetails;
		const AnimationType m_type;
		int m_currentFrame;
		bool m_animationFinished;
		bool m_proceedToNextID;
		bool m_animationPlaying;
		bool m_reverseAnimation;
		Timer m_frameTimer;

		void reset();

	private:
		void handleBaseAnimation(float deltaTime);
		void updateHorizontalAnimation(float deltaTime);
		void updateVerticalAnimation(float deltaTime);
	};

public:
	AnimationPlayer();

	void switchToAnimation(Rectangle& spriteRect, AnimationName name);
	void initialize(EntityName entityName);
	void update(Rectangle& spriteRect, float deltaTime);

private:
	std::unordered_map<AnimationName, Animation> m_animations;
	Animation* m_currentAnimation;
};