#include "AnimationPlayer.h"
#include "../Managers/EntityAnimations.h"
#include "AnimationDetails.h"
#include <assert.h>
#include "../Window.h"
#include "../Managers/TextureManager.h"

//const AnimationDetails& m_animationDetails;
//const int m_startFrame;
//const int m_endFrame;
//const std::string m_tileSheetName;
//int m_currentID;
//int m_currentFrame;
//bool m_animationFinished;
//bool m_proceedToNextFrame;
//bool m_animationPlaying;
//bool m_reverseAnimation;
//Timer m_frameTimer;

//Animation
AnimationPlayer::AnimationBase::AnimationBase(const AnimationDetails & details)
	: m_animationDetails(details),
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

void AnimationPlayer::AnimationBase::update()
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

void AnimationPlayer::AnimationBase::reset()
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

//Horizontal Animation
AnimationPlayer::HorizontalAnimation::HorizontalAnimation(const AnimationDetails& details)
	: AnimationBase(details)
{

}

void AnimationPlayer::HorizontalAnimation::update()
{
	//AnimationBase::update(deltaTime);
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

//Vertical Animation
AnimationPlayer::VerticalAnimation::VerticalAnimation(const AnimationDetails& details)
	: AnimationBase(details)
{
}

void AnimationPlayer::VerticalAnimation::update()
{
	//AnimationBase::update(deltaTime);
	if (!m_proceedToNextFrame)
	{
		return;
	}

	m_proceedToNextFrame = false;
	//const auto& tileSheet = TileSheetManagerLocator::getTileSheetManager().getTileSheet(m_tileSheetName);
	//if (m_reverseAnimation)
	//{
	//	if (m_currentFrame < m_startFrame)
	//	{
	//		m_currentFrame += tileSheet.m_columns;
	//	}
	//	else if (m_currentFrame > m_startFrame)
	//	{
	//		m_currentFrame -= tileSheet.m_columns;
	//	}
	//}
	//else
	//{
	//	if (m_currentFrame < m_endFrame)
	//	{
	//		m_currentFrame += tileSheet.m_columns;
	//	}
	//	else if (m_currentFrame > m_endFrame)
	//	{
	//		m_currentFrame -= tileSheet.m_columns;
	//	}
	//}
}

//Animation Player
AnimationPlayer::AnimationPlayer()
{
}

void AnimationPlayer::initialize(EntityName entityName)
{
	//Initialize Animations
	const auto& entityAnimations = EntityAnimations::getInstance().getAllEntityAnimations(entityName);
	for (const auto& entityAnimation : entityAnimations)
	{
		if (entityAnimation.m_direction == "Horizontal")
		{
			m_animations.emplace(entityAnimation.m_name, std::make_unique<HorizontalAnimation>(entityAnimation));
		}
		else if (entityAnimation.m_direction == "Vertical")
		{
			m_animations.emplace(entityAnimation.m_name, std::make_unique<VerticalAnimation>(entityAnimation));
		}
	}

	//Initialize Sprite
	//Temporary
	std::string stringEntityName;
	switch (entityName)
	{
	case EntityName::Player :
	{
		stringEntityName = std::string("Player");
		break;
	}
	case EntityName::Projectile :
	{
		stringEntityName = std::string("Projectile");
		break;
	}
	case EntityName::Enemy :
	{
		stringEntityName = std::string("Enemy");
		break;
	}
	}

	m_sprite.setTexture(stringEntityName);
	auto iter = m_animations.find(AnimationName::Default);
	assert(iter != m_animations.cend());
	m_currentAnimation = iter->second.get();
}

void AnimationPlayer::update()
{
	assert(m_currentAnimation);
	m_currentAnimation->update();
}

void AnimationPlayer::setPosition(Vector2i position)
{
	m_sprite.moveBy(position);
}

void AnimationPlayer::draw(const Window& window) const
{
	window.blit(m_sprite);
}