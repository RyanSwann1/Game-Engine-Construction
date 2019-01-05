#include "TextureManager.h"
#include <utility>
#include <cassert>
#include "../Utilities.h"

TextureManager::TextureManager()
	: m_textures()
{}

void TextureManager::loadTexture(const std::string& name)
{
	auto iter = m_textures.find(name);
	assert(iter == m_textures.cend());
	
	m_textures.emplace(name, (name));
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

const Texture& TextureManager::getTexture(const std::string & name) const
{
	auto iter = m_textures.find(name);
	assert(iter != m_textures.cend());
	return iter->second;
}