#pragma once

#include <memory>
#include <string>
class Level;
class EntityManager;
namespace LevelParser
{
	Level parseLevel(const std::string& fileDirectory, const std::string& levelName, EntityManager& entityManager);
}