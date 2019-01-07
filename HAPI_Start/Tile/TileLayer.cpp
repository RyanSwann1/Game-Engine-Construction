#include "TileLayer.h"

std::vector<Tile> initializeTileLayer(const std::vector<std::vector<int>>& tileMap, Vector2i mapSize, int tileSize)
{
	std::vector<Tile> tileLayer;

	for (int y = 0; y < mapSize.m_y; ++y)
	{
		for (int x = 0; x < mapSize.m_x; ++x)
		{
			const int tileID = tileMap[y][x];
			if (tileID >= 0)
			{
				tileLayer.emplace_back(tileID, Vector2i(x * tileSize, y * tileSize), tileSize);
			}
		}
	}

	return tileLayer;
}

TileLayer::TileLayer(const std::vector<std::vector<int>>& tileLayer, Vector2i mapSize, int tileSize)
	: m_tileLayer(initializeTileLayer(tileLayer, mapSize, tileSize))
{}

void TileLayer::draw(const Window & window) const
{
	for (const auto& tile : m_tileLayer)
	{
		tile.draw(window);
	}
}