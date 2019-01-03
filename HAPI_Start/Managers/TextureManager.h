#pragma once

#include <unordered_map>
#include "../Vector2i.h"
#include <string>
#include <HAPI_lib.h>
#include "../Texture.h"

using namespace HAPISPACE;

class TextureManager
{
public:
	static TextureManager& getInstance()
	{
		static TextureManager instance;
		return instance;
	}
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;
	TextureManager(TextureManager&&) = delete;
	TextureManager&& operator=(TextureManager&&) = delete;

	const Texture& getTexture(const std::string& name) const;

	void loadTexture(const std::string& name);
	void unloadTexture(const std::string& name);

private:
	TextureManager();
	std::unordered_map<std::string, Texture> m_textures;
};