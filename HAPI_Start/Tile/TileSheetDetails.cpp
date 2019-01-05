#include "TileSheetDetails.h"
#include <utility>

TileSheetDetails::TileSheetDetails(std::string && name, int columns, int rows)
	: m_name(std::move(name)),
	m_columns(columns),
	m_rows(rows)
{}
