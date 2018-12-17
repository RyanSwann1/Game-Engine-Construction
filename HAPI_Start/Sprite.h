#pragma once

#include "Vector2i.h"
#include <string>

class TextureManager;
class Texture;
class Window;
class Sprite
{
public:
	Sprite(const std::string& textureName, TextureManager& textureManager, Vector2i size, Vector2i startingPosition);

	const Texture& getTexture() const;
	Vector2i getPosition() const;

	void moveBy(Vector2i windowSize, Vector2i position);

private:

	const Texture& m_texture;
	const Vector2i m_size;
	Vector2i m_position;
};