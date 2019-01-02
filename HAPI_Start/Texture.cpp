#include "Texture.h"
#include <assert.h>
#include <utility>
#include <HAPI_lib.h>
#include "Utilities.h"

HAPISPACE::BYTE* loadTexture(const std::string& name, Vector2i& size)
{
	HAPISPACE::BYTE* texture = nullptr;
	const bool textureLoaded = HAPI.LoadTexture(name, &texture, size.m_x, size.m_y);
	assert(textureLoaded);
	return texture;
}

Texture::Texture(const std::string& name)
	: m_texture(loadTexture(name, m_size))
{}

//Texture::Texture(Texture &t)
//	: m_size(t.m_size),
//	m_texture(t.m_texture)
//{
//	t.m_texture = nullptr;
//}
//
//Texture::Texture(Texture&& t)
//	: m_size(t.m_size),
//	m_texture(t.m_texture)
//{
//	t.m_texture = nullptr;
//}

Texture::~Texture()
{
	delete[] m_texture;
	m_texture = nullptr;
}