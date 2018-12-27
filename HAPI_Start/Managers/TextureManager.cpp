#include "TextureManager.h"
#include <utility>
#include <cassert>
#include "../Utilities.h"

TextureManager::TextureManager()
	: m_textures()
{}

void TextureManager::loadTexture(std::string&& name)
{
	Vector2i textureSize;
	BYTE* textureData = nullptr;
	if (!HAPI.LoadTexture(Utilities::getDataDirectory() + name, &textureData, textureSize.m_x, textureSize.m_y))
	{
		Utilities::displayErrorMessage("Cannot find texture: " + Utilities::getDataDirectory() + name);
		return;
	}
	
	auto iter = m_textures.find(name);
	if (iter != m_textures.cend())
	{
		delete textureData;
		assert(iter == m_textures.cend());
		return;
	}
	
	m_textures.emplace(std::make_pair(std::move(name), Texture(textureSize, textureData)));
}

void TextureManager::unloadTexture(const std::string & name)
{
	auto iter = m_textures.find(name);
	if (iter == m_textures.cend())
	{
		Utilities::displayErrorMessage("Texture: " + name + " not found.");
		return;
	}

	m_textures.erase(iter);
}

Texture& TextureManager::getTexture(const std::string & name)
{
	auto iter = m_textures.find(name);
	assert(iter != m_textures.cend());
	return iter->second;
}