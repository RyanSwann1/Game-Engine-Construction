#pragma once

#include "TileLayer.h"

//class Level
//{
//public:
//	Level(std::vector<TileLayer>&& tileLayers, const std::string& levelName, const sf::Vector2i& levelSize, int tileSize);
//
//	const sf::Vector2i& getSize() const;
//	const std::string& getName() const;
//	int getTileSize() const;
//
//	void draw(sf::RenderWindow& window);
//
//private:
//	std::vector<TileLayer> m_tileLayers;
//	const std::string m_levelName;
//	const sf::Vector2i m_levelSize;
//	const int m_tileSize;
//};

class Window;
class Level
{
public:
	Level(std::vector<TileLayer>&& tileLayers, const std::string& levelName, Vector2i levelSize, int tileSize);

	void draw(const Window& window) const;

private:
	const std::vector<TileLayer> m_tileLayers;
	const std::string m_levelName;
	const Vector2i m_levelSize;
	const int m_tileSize;
};