#include "Sprite.h"
#include "HAPI_lib.h"
#include "../Managers/TextureManager.h"
#include "Texture.h"
#include "Window.h"

Sprite::Sprite(const std::string& textureName, TextureManager& textureManager, Vector2i size, Vector2i startingPosition)
	: m_texture(textureManager.getTexture(textureName)),
	m_size(size),
	m_position(startingPosition)
{}

const Texture & Sprite::getTexture() const
{
	return m_texture;
}

Vector2i Sprite::getPosition() const
{
	return m_position;
}

void Sprite::moveBy(Vector2i windowSize, Vector2i position)
{
	const Vector2i newPosition(m_position.m_x + position.m_x, m_position.m_y + position.m_y);
	if (newPosition.m_x > 0 &&
		newPosition.m_y > 0 &&
		newPosition.m_x + m_size.m_x < windowSize.m_x &&
		newPosition.m_y + m_size.m_y < windowSize.m_y)
	{
		m_position = newPosition;
	}
}