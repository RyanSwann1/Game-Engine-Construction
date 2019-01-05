#pragma once

#include "Vector2i.h"
#include "Rectangle.h"
#include <string>

class Texture;
class Window;
class Sprite
{
public:
	Sprite();

	const Texture& getTexture() const;
	void setTexture(const std::string& name);
	void setTexture(Texture& texture) { m_texture = &texture; }
	void setRect(int x, int y, int width, int height);
	Rectangle getRect() const { return m_rect; }

private:
	const Texture* m_texture;
	Rectangle m_rect;
};