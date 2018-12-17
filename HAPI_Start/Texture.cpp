#include "Texture.h"
#include <assert.h>
#include <utility>

Texture::Texture(Vector2i size, BYTE* texture)
	: m_size(size),
	m_texture(texture)
{}


Texture::Texture(Texture &t)
	: m_size(t.m_size),
	m_texture(t.m_texture)
{
	t.m_texture = nullptr;
}

Texture::Texture(Texture&& t)
	: m_size(t.m_size),
	m_texture(t.m_texture)
{
	t.m_texture = nullptr;
}

Texture::~Texture()
{
	delete[] m_texture;
	m_texture = nullptr;
}

Vector2i Texture::getSize() const
{
	return m_size;
}

const BYTE * Texture::getTextureData() const
{
	assert(m_texture);
	return m_texture;
}