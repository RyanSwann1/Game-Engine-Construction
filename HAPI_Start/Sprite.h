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

	Rectangle m_rect;

private:
	const Texture* m_texture;
	
};