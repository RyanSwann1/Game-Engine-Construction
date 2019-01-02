#include "Sprite.h"
#include "HAPI_lib.h"
#include "../Managers/TextureManager.h"
#include "Texture.h"
#include "Window.h"
#include <assert.h>

Sprite::Sprite()
	: m_texture(nullptr),
	m_size(),
	m_position()
{}

const Texture & Sprite::getTexture() const
{
	assert(m_texture);
	return *m_texture;
}

Vector2i Sprite::getPosition() const
{
	return m_position;
}

void Sprite::setTexture(const std::string & name)
{
	m_texture = &TextureManager::getInstance().getTexture(name);
}

void Sprite::moveBy(Vector2i moveAmount)
{
	m_position += moveAmount;
}

//void Sprite::moveBy(Vector2i windowSize, Vector2i position)
//{
//	const Vector2i newPosition(m_position.m_x + position.m_x, m_position.m_y + position.m_y);
//	if (newPosition.m_x > 0 &&
//		newPosition.m_y > 0 &&
//		newPosition.m_x + m_size.m_x < windowSize.m_x &&
//		newPosition.m_y + m_size.m_y < windowSize.m_y)
//	{
//		m_position = newPosition;
//	}
//}