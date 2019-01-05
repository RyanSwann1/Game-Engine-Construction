#pragma once

#include "../Tile/TileSheetDetails.h"
#include <unordered_map>
#include <string>

class TileSheetDetailsManager
{
public:
	static TileSheetDetailsManager& getInstance()
	{
		static TileSheetDetailsManager instance;
		return instance;
	}
	const TileSheetDetails& getTileSheetDetails(const std::string& tileSheetName) const;

private:
	TileSheetDetailsManager();
	std::unordered_map<std::string, TileSheetDetails> m_tileSheetDetails;
};