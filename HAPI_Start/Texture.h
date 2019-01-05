#pragma once

using BYTE = unsigned char;
#include "Vector2i.h"
#include <string>

class Texture
{
public:
	Texture(const std::string& name);
	//Texture(Texture& t);
	//Texture(Texture&& t);
	~Texture();

	BYTE* m_texture;
	Vector2i m_size;
};