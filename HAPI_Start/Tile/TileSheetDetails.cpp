#include "TileSheetDetails.h"
#include <utility>

TileSheetDetails::TileSheetDetails(std::string && name, int tileSize, int columns, int rows, int firstGID, int margin, int spacing)
	: m_name(std::move(name)),
	m_tileSize(tileSize),
	m_columns(columns),
	m_rows(rows),
	m_firstGID(firstGID),
	m_margin(margin),
	m_spacing(spacing)
{
}
