#include "Window.h"
#include <utility>
#include <cassert>
#include "Vector2f.h"
#include "Vector3f.h"
#include "Utilities.h"
#include "Sprite.h"
#include "Texture.h"

Window::Window(const std::string& name, Vector2i size)
	: m_windowSize(size),
	m_maxEyeDistance(200),
	m_minEyeDistance(0),
	m_eyeDistance(100)
{
	Utilities::displayFPSIndicator(Vector2i(850, 50));
}

Window * Window::create(const std::string & name, Vector2i size)
{
	Vector2i windowSize = size;
	if (!HAPI.Initialise(windowSize.m_x, windowSize.m_y, name))
	{
		return nullptr;
	}

	return new Window(name, windowSize);
}

unsigned int Window::getOffSet(Vector2f position) const
{
	return (position.m_x + position.m_y * m_windowSize.m_x) * 4;
}

unsigned int Window::getOffSet(Vector3f position) const
{
	return (position.m_x + position.m_y * m_windowSize.m_x) * 4;
}

unsigned int Window::getOffSet(Vector2i position) const
{
	return (position.m_x + position.m_y * m_windowSize.m_x) * 4;
}

int Window::getEyeDistance() const
{
	return m_eyeDistance;
}

BYTE * Window::getScreen() const
{
	return HAPI.GetScreenPointer();
}

Vector2i Window::getSize()
{
	return m_windowSize;
}

void Window::blit(const Sprite & sprite) const
{
	Vector2i spritePosition = sprite.getPosition();
	BYTE* screenPointer = HAPI.GetScreenPointer() + (spritePosition.m_x + spritePosition.m_y * m_windowSize.m_x) * BYTES_PER_PIXEL;
	const BYTE* texture = sprite.getTexture().getTextureData();

	for (int y = 0; y < sprite.getTexture().getSize().m_y; ++y)
	{
		memcpy(screenPointer, texture, sprite.getTexture().getSize().m_x * BYTES_PER_PIXEL);

		texture += sprite.getTexture().getSize().m_x * BYTES_PER_PIXEL;
		screenPointer += m_windowSize.m_x * BYTES_PER_PIXEL;
	}
}

void Window::blit(const Sprite & sprite, float i) const
{
	BYTE* screen = HAPI.GetScreenPointer();
	const BYTE* texture = sprite.getTexture().getTextureData();
	Vector2i textureSize = sprite.getTexture().getSize();

	const int endOfLineScreenIncrement = (m_windowSize.m_x - textureSize.m_x) * 4;
	for (int y = 0; y < textureSize.m_y; ++y)
	{
		for (int x = 0; x < textureSize.m_x * 4; x += 4)
		{
			const BYTE blue = texture[0];
			const BYTE green = texture[1];
			const BYTE red = texture[2];
			const BYTE alpha = texture[3];
			const float mod = alpha / i;
			screen[0] = (BYTE)(mod*blue + (1.0f - mod) * screen[0]);
			screen[1] = (BYTE)(mod*green + (1.0f - mod) * screen[1]);
			screen[2] = (BYTE)(mod*red + (1.0f - mod) * screen[2]);
		
			screen += 4;
			texture += 4;
		}
		screen += endOfLineScreenIncrement; 
	}
}

void Window::clearScreenToBlack() const
{
	BYTE* screen = HAPI.GetScreenPointer();
	for (int i = 0; i < m_windowSize.m_x * m_windowSize.m_y * BYTES_PER_PIXEL; i += BYTES_PER_PIXEL)
	{
		screen[i + 0] = 0;
		screen[i + 1] = 0;
		screen[i + 2] = 0;
	}
}

void Window::clearScreenToGrey() const
{
	memset(HAPI.GetScreenPointer(), 128, m_windowSize.m_x * m_windowSize.m_y * BYTES_PER_PIXEL);
}