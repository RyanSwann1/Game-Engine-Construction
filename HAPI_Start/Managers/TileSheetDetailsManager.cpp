#include "TileSheetDetailsManager.h"
#include <assert.h>

TileSheetDetailsManager::TileSheetDetailsManager()
	: m_tileSheetDetails()
{
	m_tileSheetDetails.emplace(std::string("character.png"), TileSheetDetails("character.png", 17));
}

const TileSheetDetails & TileSheetDetailsManager::getTileSheetDetails(const std::string & tileSheetName) const
{
	auto iter = m_tileSheetDetails.find(tileSheetName);
	assert(iter != m_tileSheetDetails.cend());
	return iter->second;
}
