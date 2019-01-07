#pragma once

#include "../Sprite.h"
#include "../Vector2i.h"

class Window;
class Tile
{
public:
	Tile(int tileID, Vector2i position, int tileSize);

	void draw(const Window& window) const;

private:
	const int m_tileID;
	const Vector2i m_position;
	Sprite m_sprite;
};