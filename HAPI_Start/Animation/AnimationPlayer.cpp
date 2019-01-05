#include "AnimationPlayer.h"
#include "../Managers/EntityAnimations.h"
#include "AnimationDetails.h"
#include "../Window.h"
#include "../Managers/TextureManager.h"
#include <assert.h>

//Animation
AnimationPlayer::Animation::Animation(const AnimationDetails & details, AnimationType type)
	: m_animationDetails(details),
	m_type(type),
	m_startFrame(0),
	m_endFrame(m_animationDetails.m_endID - m_animationDetails.m_startID),
	m_currentID(0),
	m_currentFrame(0),
	m_animationFinished(false),
	m_proceedToNextFrame(false),
	m_animationPlaying(false),
	m_reverseAnimation(false),
	m_frameTimer()
{}

void AnimationPlayer::Animation::update(Rectangle& spriteRect)
{
	handleBaseAnimation();

	switch (m_type)
	{
	case AnimationType::Horizontal :
	{
		updateHorizontalAnimation();
		break;
	}
	case AnimationType::Vertical :
	{
		updateVerticalAnimation();
		break;
	}
	}
}

void AnimationPlayer::Animation::reset()
{
	m_animationFinished = false;
	m_proceedToNextFrame = false;
	m_animationPlaying = m_animationDetails.m_repeatable;
	if (m_animationPlaying)
	{
		m_currentFrame = m_startFrame;
	}
	m_frameTimer.reset();
}

void AnimationPlayer::Animation::handleBaseAnimation()
{
	if (!m_animationPlaying)
	{
		return;
	}

	if (!m_frameTimer.isActive())
	{
		return;
	}

	//m_frameTimer.update(deltaTime);
	if (!m_frameTimer.isExpired())
	{
		return;
	}

	if (m_currentFrame == m_endFrame)
	{
		if (m_animationDetails.m_reversible)
		{
			m_reverseAnimation = true;
		}
		else
		{
			reset();
			return;
		}
	}

	if (m_reverseAnimation && m_currentFrame == m_startFrame)
	{
		reset();
		return;
	}

	m_proceedToNextFrame = true;
	m_frameTimer.reset();
}

void AnimationPlayer::Animation::updateHorizontalAnimation()
{
		if (!m_proceedToNextFrame)
		{
			return;
		}
		m_proceedToNextFrame = false;

		if (m_reverseAnimation)
		{
			if (m_currentFrame > m_startFrame)
			{
				--m_currentFrame;
			}
			else if (m_currentFrame < m_startFrame)
			{
				++m_currentFrame;
			}
		}
		else
		{
			if (m_currentFrame > m_endFrame)
			{
				--m_currentFrame;
			}
			else if (m_currentFrame < m_endFrame)
			{
				++m_currentFrame;
			}
		}
}

void AnimationPlayer::Animation::updateVerticalAnimation()
{
	if (!m_proceedToNextFrame)
	{
		return;
	}

	/*m_proceedToNextFrame = false;
	const auto& tileSheet = TileSheetManagerLocator::getTileSheetManager().getTileSheet(m_tileSheetName);
	if (m_reverseAnimation)
	{
		if (m_currentFrame < m_startFrame)
		{
			m_currentFrame += tileSheet.m_columns;
		}
		else if (m_currentFrame > m_startFrame)
		{
			m_currentFrame -= tileSheet.m_columns;
		}
	}
	else
	{
		if (m_currentFrame < m_endFrame)
		{
			m_currentFrame += tileSheet.m_columns;
		}
		else if (m_currentFrame > m_endFrame)
		{
			m_currentFrame -= tileSheet.m_columns;
		}
	}*/
}


//Animation Player
AnimationPlayer::AnimationPlayer() 
	: m_animations(),
	m_currentAnimation(nullptr)
{
}

void AnimationPlayer::initialize(EntityName entityName)
{
	const auto& entityAnimations = EntityAnimations::getInstance().getAllEntityAnimations(entityName);
	for (const AnimationDetails& animationDetails : entityAnimations)
	{
		if (animationDetails.m_direction == "Horizontal")
		{
			m_animations.emplace(animationDetails.m_name, Animation(animationDetails, AnimationType::Horizontal));
		}
		else if (animationDetails.m_direction == "Vertical")
		{
			m_animations.emplace(animationDetails.m_name, Animation(animationDetails, AnimationType::Vertical));
		}
	}

	auto iter = m_animations.find(AnimationName::Default);
	assert(iter != m_animations.cend());
	m_currentAnimation = &iter->second;
}

void AnimationPlayer::update(Rectangle& spriteRect)
{
	if (m_currentAnimation)
	{
		return;
	}

	m_currentAnimation->update(spriteRect);
}