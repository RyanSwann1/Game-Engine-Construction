#include "LevelParser.h"
#include "Utilities/Base64.h"
#include "Utilities/tinyxml.h"
#include "Managers/EntityManager.h"
#include "EntityNameConverter.h"
#include "Tile/TileSheetDetails.h"
#include "Managers/TileSheetDetailsManager.h"
#include "Tile/Level.h"
#include <assert.h>

class LevelDetails
{
public:
	LevelDetails(Vector2i size, int tileSize)
		: m_levelSize(size),
		m_tileSize(tileSize)
	{}

	const Vector2i m_levelSize;
	const int m_tileSize;
};

std::vector<TileLayer> parseTileLayers(const TiXmlElement& rootElement, const LevelDetails& levelDetails);
std::vector<Vector2i> parseCollisionLayer(const TiXmlElement& rootElement, int tileSize);
LevelDetails parseLevelDetails(const TiXmlElement& rootElement);
std::vector<std::vector<int>> decodeTileLayer(const TiXmlElement & tileLayerElement, Vector2i levelSize);
void parseTileSheets(const TiXmlElement& rootElement);
void parseEntities(const TiXmlElement& rootElement, EntityManager& entityManager, int tileSize);

Level LevelParser::parseLevel(const std::string& fileDirectory, const std::string& levelName, EntityManager& entityManager)
{
	TiXmlDocument mapFile;
	const bool mapLoaded = mapFile.LoadFile("MapOne.tmx");
	assert(mapLoaded);

	const auto& rootElement = mapFile.RootElement();
	const LevelDetails levelDetails = parseLevelDetails(*rootElement);
	parseTileSheets(*rootElement);
	parseEntities(*rootElement, entityManager, levelDetails.m_tileSize);

	return Level(std::move(parseTileLayers(*rootElement, levelDetails)),
		levelName, levelDetails.m_levelSize, levelDetails.m_tileSize);
}

void parseTileSheets(const TiXmlElement& rootElement)
{
	for (const auto* tileSheetElement = rootElement.FirstChildElement();
		tileSheetElement != nullptr; tileSheetElement = tileSheetElement->NextSiblingElement())
	{
		if (tileSheetElement->Value() != std::string("tileset"))
		{
			continue;
		}

		int tileSheetFirstGID = 0;
		//tileSheetElement->Attribute("firstgid", &tileSheetFirstGID);
		auto& tileSheetDetailsManager = TileSheetDetailsManager::getInstance();
		//auto& tileSheetManager = TileSheetManagerLocator::getTileSheetManager();
		std::string tileSheetName = tileSheetElement->Attribute("name");
		if ( tileSheetDetailsManager.hasTileSheet(tileSheetName))
		{
			continue;
		}

		Vector2i tileSetSize;
		int spacing = 0, margin = 0, tileSize = 0, firstGID = 0;
		tileSheetElement->Attribute("width", &tileSetSize.m_x);
		tileSheetElement->Attribute("height", &tileSetSize.m_y);
		//tileSheetElement->FirstChildElement()->Attribute("width", &tileSetSize.m_x);
		//tileSheetElement->FirstChildElement()->Attribute("height", &tileSetSize.m_y);
		tileSheetElement->Attribute("tilewidth", &tileSize);
		tileSheetElement->Attribute("spacing", &spacing);
		tileSheetElement->Attribute("firstgid", &firstGID);
		tileSheetElement->Attribute("margin", &margin);
		const int columns = tileSetSize.m_x / (tileSize + spacing);
		const int rows = tileSetSize.m_y / (tileSize + spacing);
		tileSheetDetailsManager.addTileSheet(TileSheetDetails(std::move(tileSheetName), tileSize, columns, rows, firstGID, margin, spacing));

	/*	TileSheetDetailsManager::getInstance().addTileSheet(tileSheetFirstGID, 
			TileSheetDetails(std::move(tileSheetName), tileSize, columns, rows, firstGID, margin, spacing));*/
	}
}

void parseEntities(const TiXmlElement & rootElement, EntityManager& entityManager, int tileSize)
{
	for (const auto* entityElementRoot = rootElement.FirstChildElement(); entityElementRoot != nullptr; entityElementRoot = entityElementRoot->NextSiblingElement())
	{
		if (entityElementRoot->Value() != std::string("objectgroup"))
		{
			continue;
		}

		if (entityElementRoot->Attribute("name") != std::string("Entity Layer"))
		{
			continue;
		}

		for (const auto* entityElement = entityElementRoot->FirstChildElement(); entityElement != nullptr; entityElement = entityElement->NextSiblingElement())
		{
			Vector2i position;
			entityElement->Attribute("x", &position.m_x);
			entityElement->Attribute("y", &position.m_y);
			const std::string entityName = entityElement->Attribute("name");

			//Tiled Hack?
			//yPosition -= tileSize;
			position.m_y -= tileSize;
			const EntityName convertedEntityName = EntityNameConverter::getInstance().getConvertedName(entityName);
			entityManager.addEntity(convertedEntityName, position);
		}
	}
}

std::vector<std::vector<int>> decodeTileLayer(const TiXmlElement & tileLayerElement, Vector2i levelSize)
{
	std::vector<std::vector<int>> tileData;
	tileData.reserve(levelSize.m_y);

	std::string decodedIDs; //Base64 decoded information
	const TiXmlElement* dataNode = nullptr; //Store our node once we find it
	for (const TiXmlElement* e = tileLayerElement.FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("data"))
		{
			dataNode = e;
		}
	}
	assert(dataNode);

	Base64 base64;
	const TiXmlText* text = dataNode->FirstChild()->ToText();
	const std::string t = text->Value();
	decodedIDs = base64.base64_decode(t);

	const std::vector<int> layerColumns(levelSize.m_x);
	for (int i = 0; i < levelSize.m_y; ++i)
	{
		tileData.push_back(layerColumns);
	}

	for (int rows = 0; rows < levelSize.m_y; ++rows)
	{
		for (int cols = 0; cols < levelSize.m_x; ++cols)
		{
			tileData[rows][cols] = *((int*)decodedIDs.data() + rows * levelSize.m_x + cols) - 1;
		}
	}

	return tileData;
}

LevelDetails parseLevelDetails(const TiXmlElement& rootElement)
{
	Vector2i levelSize;
	int tileSize = 0;
	rootElement.Attribute("width", &levelSize.m_x);
	rootElement.Attribute("height", &levelSize.m_y);
	rootElement.Attribute("tilewidth", &tileSize);
	return LevelDetails(levelSize, tileSize);
}

std::vector<TileLayer> parseTileLayers(const TiXmlElement & rootElement, const LevelDetails& levelDetails)
{
	std::vector<TileLayer> tileLayers;
	for (const auto* tileLayerElement = rootElement.FirstChildElement(); tileLayerElement != nullptr; tileLayerElement = tileLayerElement->NextSiblingElement())
	{
		if (tileLayerElement->Value() != std::string("layer"))
		{
			continue;
		}

		auto tileMap = decodeTileLayer(*tileLayerElement, levelDetails.m_levelSize);
		tileLayers.emplace_back(std::move(tileMap), levelDetails.m_levelSize, levelDetails.m_tileSize);
	}

	assert(!tileLayers.empty());
	return tileLayers;
}

std::vector<Vector2i> parseCollisionLayer(const TiXmlElement & rootElement, int tileSize)
{
	std::vector<Vector2i> collidablePositions;
	for (const auto* collisionLayerElement = rootElement.FirstChildElement(); collisionLayerElement != nullptr;
		collisionLayerElement = collisionLayerElement->NextSiblingElement())
	{
		if (collisionLayerElement->Value() != std::string("objectgroup"))
		{
			continue;
		}

		if (collisionLayerElement->Attribute("name") != std::string("Collision Layer"))
		{
			continue;
		}

		for (const auto* collisionElement = collisionLayerElement->FirstChildElement();
			collisionElement != nullptr; collisionElement = collisionElement->NextSiblingElement())
		{
			int xPosition = 0, yPosition = 0;
			collisionElement->Attribute("x", &xPosition);
			collisionElement->Attribute("y", &yPosition);
			//Hack for Tiled.
			yPosition -= tileSize;
			collidablePositions.emplace_back(xPosition, yPosition);
		}
	}

	assert(!collidablePositions.empty());
	return collidablePositions;
}