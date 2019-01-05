#include "TileSheetDetails.h"
#include <utility>

TileSheetDetails::TileSheetDetails(std::string && name, int columns)
	: m_name(std::move(name)),
	m_columns(columns),
	m_tileSize(16)
{}
