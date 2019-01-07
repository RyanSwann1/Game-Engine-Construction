#pragma once

#include <string>
#include <vector>
#include <memory>
#include "../Tile/Level.h"

class EntityManager;
class Window;
class LevelManager
{
public:
	LevelManager();
	LevelManager(const LevelManager&) = delete;
	LevelManager& operator=(const LevelManager&) = delete;
	LevelManager(LevelManager&&) = delete;
	LevelManager&& operator=(LevelManager&&) = delete;

	void draw(const Window& window) const;
	void loadLevel(EntityManager& entityManager);

private:
	std::unique_ptr<Level> m_level;
};