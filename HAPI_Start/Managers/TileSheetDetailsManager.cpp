#include "TileSheetDetailsManager.h"
#include <assert.h>

TileSheetDetailsManager::TileSheetDetailsManager()
	: m_tileSheetDetails()
{
}

const TileSheetDetails & TileSheetDetailsManager::getTileSheetDetails(const std::string & tileSheetName) const
{
	auto iter = m_tileSheetDetails.find(tileSheetName);
	assert(iter != m_tileSheetDetails.cend());
	return iter->second;
}

bool TileSheetDetailsManager::hasTileSheet(const std::string & name) const
{
	auto iter = m_tileSheetDetails.find(name);
	return (iter != m_tileSheetDetails.cend());
}

void TileSheetDetailsManager::addTileSheet(const TileSheetDetails & tileSheetDetails)
{
	assert(m_tileSheetDetails.find(tileSheetDetails.m_name) == m_tileSheetDetails.cend());
	m_tileSheetDetails.emplace(tileSheetDetails.m_name, tileSheetDetails);
}
