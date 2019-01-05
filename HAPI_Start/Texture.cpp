#include "Texture.h"
#include <assert.h>
#include <utility>
#include <HAPI_lib.h>
#include "Utilities.h"


Texture::Texture(const std::string& name)
	: m_texture(nullptr),
		m_size()
{
	const bool textureLoaded = HAPI.LoadTexture(Utilities::getDataDirectory() + name, &m_texture, m_size.m_x, m_size.m_y);
	assert(textureLoaded);
}

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
	assert(m_texture);
	delete[] m_texture;
	m_texture = nullptr;
}