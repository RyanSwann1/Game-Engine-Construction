#pragma once

#include <string>

class TileSheetDetails
{
public:
	TileSheetDetails(std::string&& name, int tileSize, int columns, int rows, int firstGID, int margin, int spacing);
	//TileSheetDetails(const TileSheetDetails&) = delete;
	//TileSheetDetails& operator=(const TileSheetDetails&) = delete;
	//TileSheetDetails(TileSheetDetails&&) = delete;
	//TileSheetDetails&& operator=(TileSheetDetails&&) = delete;

	const std::string m_name;
	const int m_tileSize;
	const int m_columns;
	const int m_rows;
	const int m_firstGID;
	const int m_margin;
	const int m_spacing;
};