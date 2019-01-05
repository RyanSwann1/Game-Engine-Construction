#pragma once

#include <string>

class TileSheetDetails
{
public:
	TileSheetDetails(std::string&& name, int columns, int rows);

	const std::string m_name;
	const int m_columns;
	const int m_rows;
};