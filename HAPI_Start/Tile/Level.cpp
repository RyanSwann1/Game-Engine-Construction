#include "Level.h"

Level::Level(std::vector<TileLayer>&& tileLayers, const std::string & levelName, Vector2i levelSize, int tileSize)
	: m_tileLayers(std::move(tileLayers)),
	m_levelName(levelName),
	m_levelSize(levelSize),
	m_tileSize(tileSize)
{}

void Level::draw(const Window & window) const
{
	for (const auto& tileLayer : m_tileLayers)
	{
		tileLayer.draw(window);
	}
}
