#pragma once

#include "../Sprite.h"
#include "AnimationName.h"
#include "../EntityName.h"
#include "../Timer.h"
#include <unordered_map>
#include <memory>

class AnimationDetails;
class Window;
class AnimationPlayer
{
	class AnimationBase
	{
	public:
		AnimationBase(const AnimationDetails& details);
		AnimationBase(const AnimationBase&) = delete;
		AnimationBase& operator=(const AnimationBase&) = delete;
		AnimationBase(AnimationBase&&) = delete;
		AnimationBase&& operator=(AnimationBase&&) = delete;

		virtual void update();

	protected:
		const AnimationDetails& m_animationDetails;
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
	};

	class HorizontalAnimation : public AnimationBase
	{
	public:
		HorizontalAnimation(const AnimationDetails& details);
		HorizontalAnimation(const HorizontalAnimation&) = delete;
		HorizontalAnimation& operator=(const HorizontalAnimation&) = delete;
		HorizontalAnimation(HorizontalAnimation&&) = delete;
		HorizontalAnimation&& operator=(HorizontalAnimation&&) = delete;
	
		void update() override;
	};

	class VerticalAnimation : public AnimationBase
	{
	public:
		VerticalAnimation(const AnimationDetails& details);
		VerticalAnimation(const VerticalAnimation&) = delete;
		VerticalAnimation& operator=(const VerticalAnimation&) = delete;
		VerticalAnimation(VerticalAnimation&&) = delete;
		VerticalAnimation&& operator=(VerticalAnimation&&) = delete;

		void update() override;
	};

public:
	AnimationPlayer();

	void initialize(EntityName entityName);
	void update();
	void setPosition(Vector2i position);
	void draw(const Window& window) const;

private:
	Sprite m_sprite;
	std::unordered_map<AnimationName, std::unique_ptr<AnimationBase>> m_animations;
	AnimationBase* m_currentAnimation;
};