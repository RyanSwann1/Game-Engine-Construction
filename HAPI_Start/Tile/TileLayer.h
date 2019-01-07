#pragma once

#include <vector>
#include "Tile.h"

class Window;
class TileLayer
{
public:
	TileLayer(const std::vector<std::vector<int>>& tileLayer, Vector2i mapSize, int tileSize);

	void draw(const Window& window) const;

private:
	const std::vector<Tile> m_tileLayer;
};