#include "AnimationPlayer.h"
#include "../Managers/EntityAnimations.h"
#include "AnimationDetails.h"
#include "../Window.h"
#include "../Managers/TextureManager.h"
#include "../Managers/TileSheetDetailsManager.h"
#include <assert.h>

//Animation
AnimationPlayer::Animation::Animation(const AnimationDetails & details, const TileSheetDetails& tileSheetDetails, AnimationType type)
	: m_animationDetails(details),
	m_tileSheetDetails(tileSheetDetails),
	m_type(type),
	m_currentFrame(details.m_startFrame),
	m_animationFinished(false),
	m_proceedToNextID(false),
	m_animationPlaying(false),
	m_reverseAnimation(false),
	m_frameTimer(details.m_frameTime)
{}

Vector2i AnimationPlayer::Animation::getDrawLocationSize() const
{
	return m_animationDetails.m_drawLocationSize;
}

const TileSheetDetails & AnimationPlayer::Animation::getTileSheetDetails() const
{
	return m_tileSheetDetails;
}

void AnimationPlayer::Animation::update(Rectangle & spriteRect, float deltaTime)
{
	//Non idle animation
	if (m_animationDetails.m_startFrame != m_animationDetails.m_endFrame)
	{
		m_frameTimer.update(deltaTime);
		if (m_frameTimer.isExpired())
		{
			if (m_currentFrame < m_animationDetails.m_endFrame)
			{
				++m_currentFrame;
			}
			else
			{
				m_currentFrame = m_animationDetails.m_startFrame;
			}

			//Current frame 
			m_frameTimer.reset();
			int i = 0;
		}
	}

	spriteRect.m_y = (m_currentFrame / m_tileSheetDetails.m_columns) * m_tileSheetDetails.m_tileSize;
	spriteRect.m_x = (m_currentFrame % m_tileSheetDetails.m_columns) * m_tileSheetDetails.m_tileSize;
}

//void AnimationPlayer::Animation::update(Rectangle& spriteRect, float deltaTime)
//{
//	handleBaseAnimation(deltaTime);
//
//	switch (m_type)
//	{
//	case AnimationType::Horizontal :
//	{
//		updateHorizontalAnimation(deltaTime);
//		break;
//	}
//	case AnimationType::Vertical :
//	{
//		updateVerticalAnimation(deltaTime);
//		break;
//	}
//	}
//}

void AnimationPlayer::Animation::reset()
{
}
//	m_animationFinished = false;
//	m_proceedToNextID = false;
//	m_animationPlaying = m_details.m_repeatable;
//	if (m_animationPlaying)
//	{
//		m_currentFrame = m_startFrame;
//	}
//	m_frameTimer.reset();
//}

void AnimationPlayer::Animation::handleBaseAnimation(float deltaTime)
{
	//if (!m_animationPlaying || !m_frameTimer.isActive())
	//{
	//	return;
	//}

	//m_frameTimer.update(deltaTime);
	//if (!m_frameTimer.isExpired())
	//{
	//	return;
	//}

	//if (m_currentFrame == m_endFrame)
	//{
	//	if (m_details.m_reversible)
	//	{
	//		m_reverseAnimation = true;
	//	}
	//	else
	//	{
	//		reset();
	//		return;
	//	}
	//}

	//if (m_reverseAnimation && m_currentFrame == m_startFrame)
	//{
	//	reset();
	//	return;
	//}

	//m_proceedToNextID = true;
	//m_frameTimer.reset();
}

void AnimationPlayer::Animation::updateHorizontalAnimation(float deltaTime)
{
		//if (!m_proceedToNextID)
		//{
		//	return;
		//}
		//m_proceedToNextID = false;
		//if (m_reverseAnimation)
		//{
		//	if (m_currentFrame > m_startFrame)
		//	{
		//		--m_currentFrame;
		//	}
		//	else if (m_currentFrame < m_startFrame)
		//	{
		//		++m_currentFrame;
		//	}
		//}
		//else
		//{
		//	if (m_currentFrame > m_endFrame)
		//	{
		//		--m_currentFrame;
		//	}
		//	else if (m_currentFrame < m_endFrame)
		//	{
		//		++m_currentFrame;
		//	}
		//}
}

void AnimationPlayer::Animation::updateVerticalAnimation(float deltaTime)
{
	if (!m_proceedToNextID)
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

void AnimationPlayer::switchToAnimation(Rectangle & spriteRect, AnimationName name)
{
	auto iter = m_animations.find(name);
	assert(iter != m_animations.cend());
	m_currentAnimation = &iter->second;

	//Assign sprite rect to the current animation drawing size.
	//Multiple animations can have different drawing sizes
	const int tileSize = m_currentAnimation->getTileSheetDetails().m_tileSize;
	spriteRect.m_width = m_currentAnimation->getDrawLocationSize().m_x * tileSize;
	spriteRect.m_height = m_currentAnimation->getDrawLocationSize().m_y * tileSize;
	int i = 0;
}

void AnimationPlayer::initialize(EntityName entityName)
{
	const auto& entityAnimations = EntityAnimations::getInstance().getAllEntityAnimations(entityName);
	for (const AnimationDetails& animationDetails : entityAnimations)
	{
		const auto& tileSheetDetails = TileSheetDetailsManager::getInstance().getTileSheetDetails(animationDetails.m_textureName);
		if (animationDetails.m_direction == "Horizontal")
		{
			m_animations.emplace(animationDetails.m_name, Animation(animationDetails, tileSheetDetails, AnimationType::Horizontal));
		}
		else if (animationDetails.m_direction == "Vertical")
		{
			m_animations.emplace(animationDetails.m_name, Animation(animationDetails, tileSheetDetails, AnimationType::Vertical));
		}
	}
}

void AnimationPlayer::update(Rectangle& spriteRect, float deltaTime)
{
	assert(m_currentAnimation);
	m_currentAnimation->update(spriteRect, deltaTime);
}