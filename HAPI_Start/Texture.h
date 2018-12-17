#pragma once

using BYTE = unsigned char;
#include "Vector2i.h"


class Texture
{
public:
	Texture(Vector2i size, BYTE* texture = nullptr);
	Texture(Texture& t);
	Texture(Texture&& t);
	~Texture();

	Vector2i getSize() const;
	const BYTE* getTextureData() const;

private:
	Vector2i m_size;
	BYTE* m_texture;
};