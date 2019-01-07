#include "LevelManager.h"
#include "../LevelParser.h"
#include "../Utilities.h"
#include "../Managers/TileSheetDetailsManager.h"

LevelManager::LevelManager()
{
}

void LevelManager::draw(const Window & window) const
{
	m_level->draw(window);
}

void LevelManager::loadLevel(EntityManager & entityManager)
{
	Level newLevel = LevelParser::parseLevel(Utilities::getDataDirectory(), "MapTwo.txt", entityManager);
	m_level = std::make_unique<Level>(newLevel);
	auto& i = TileSheetDetailsManager::getInstance().getAll();
	int j = 0;
}