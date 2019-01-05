#include "Sprite.h"
#include "HAPI_lib.h"
#include "../Managers/TextureManager.h"
#include "Texture.h"
#include "Window.h"
#include <assert.h>

Sprite::Sprite()
	: m_texture(nullptr),
	m_rect()
{}

const Texture & Sprite::getTexture() const
{
	assert(m_texture);
	return *m_texture;
}

void Sprite::setTexture(const std::string & name)
{
	m_texture = &TextureManager::getInstance().getTexture(name);
}

//void Sprite::setRect(int x, int y, int width, int height)
//{
//	m_rect.m_width = width;
//	m_rect.m_height = height;
//	m_rect.m_x = x;
//	m_rect.m_y = y;
//}
//
//void Sprite::setRectPosition(Vector2i position)
//{
//	m_rect.m_x = position.m_x;
//	m_rect.m_y = position.m_y;
//}
