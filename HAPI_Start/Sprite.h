#pragma once

#include "Vector2i.h"
#include <string>

class TextureManager;
class Texture;
class Window;
class Sprite
{
public:
	Sprite();

	const Texture& getTexture() const;
	Vector2i getPosition() const;
	void setTexture(const std::string& name);

	void moveBy(Vector2i moveAmount);
	//void moveBy(Vector2i windowSize, Vector2i position);

private:
	const Texture* m_texture;
	Vector2i m_size;
	Vector2i m_position;
};