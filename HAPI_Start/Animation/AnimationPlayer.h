#pragma once

#include "../Sprite.h"
#include "AnimationName.h"
#include "../Timer.h"
#include <unordered_map>

enum class EntityName;
class AnimationDetails;
class Rectangle;
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
		Animation(const AnimationDetails& details, AnimationType type);

		void update(Rectangle& spriteRect);

	protected:
		const AnimationDetails& m_animationDetails;
		const AnimationType m_type;
		const int m_startFrame;
		const int m_endFrame;
		int m_currentID;
		int m_currentFrame;
		bool m_animationFinished;
		bool m_proceedToNextFrame;
		bool m_animationPlaying;
		bool m_reverseAnimation;
		Timer m_frameTimer;

		void reset();

	private:
		void handleBaseAnimation();
		void updateHorizontalAnimation();
		void updateVerticalAnimation();
	};

public:
	AnimationPlayer();

	void initialize(EntityName entityName);
	void update(Rectangle& spriteRect);

private:
	std::unordered_map<AnimationName, Animation> m_animations;
	Animation* m_currentAnimation;
};