#include "Tile.h"
#include "../Window.h"
#include "../Managers/TileSheetDetailsManager.h"

Tile::Tile(int tileID, Vector2i position, int tileSize)
	: m_tileID(tileID),
	m_position(position),
	m_sprite(tileSize, tileSize)
{
	/*spriteRect.m_y = (m_currentFrame / m_tileSheetDetails.m_columns) * m_tileSheetDetails.m_tileSize;
	spriteRect.m_x = (m_currentFrame % m_tileSheetDetails.m_columns) * m_tileSheetDetails.m_tileSize;*/
	m_sprite.setTexture("Overworld.png");
	auto& i = TileSheetDetailsManager::getInstance().getTileSheetDetails("Overworld");
	m_sprite.m_rect.m_x = (m_tileID % i.m_columns) * 16;
	m_sprite.m_rect.m_y = (m_tileID / i.m_columns) * 16;
	int j = 0;
}

void Tile::draw(const Window & window) const
{
	window.draw(m_sprite, m_position);
}
