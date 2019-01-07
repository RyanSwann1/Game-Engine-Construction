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

	const std::unordered_map<std::string, TileSheetDetails>& getAll() { return m_tileSheetDetails; }
	const TileSheetDetails& getTileSheetDetails(const std::string& tileSheetName) const;
	bool hasTileSheet(const std::string& name) const;

	void addTileSheet(const TileSheetDetails& tileSheetDetails);
	

private:
	TileSheetDetailsManager();
	std::unordered_map<std::string, TileSheetDetails> m_tileSheetDetails;
};