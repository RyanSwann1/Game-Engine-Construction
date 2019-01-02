#include "Window.h"
#include <utility>
#include <cassert>
#include "Vector2f.h"
#include "Vector3f.h"
#include "Utilities.h"
#include "Sprite.h"
#include "Texture.h"

Window::Window(Vector2i size)
	: m_windowSize(size),
	m_maxEyeDistance(200),
	m_minEyeDistance(0),
	m_eyeDistance(100)
{
	Utilities::displayFPSIndicator(Vector2i(250, 250));
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

//void Texture::BlitFast(HAPISPACE::BYTE* screen, Vector2i screenSize, const Vector2i& pos, const Rect& area) const
//{
//	const BYTE* currentTexturePixel = m_texture;
//	currentTexturePixel += (area.Left + (m_width * area.Top)) * 4;
//	const Vector2i center_screen = screenSize / 2;
//
//	const int width = area.Right - area.Left;
//	const int height = area.Bottom - area.Top;
//
//	BYTE* currentScreenPixel = screen + (std::clamp(pos.x, 0, screenSize.x) + std::clamp(pos.y, 0, screenSize.y) * screenSize.x) * 4;
//
//	for (size_t y = 0; y < height; y++)
//	{
//		memcpy(currentScreenPixel, currentTexturePixel, width * 4);
//		//add the rest of the sprite width to get to the next line of the texture
//		currentTexturePixel += m_width * 4;
//		//move screen to pointer
//		currentScreenPixel += screenSize.x * 4;
//	}
//}

//for (int y = 0; y < textureHeight; y++)
//{
//	memcpy(screenPnter, texturePnter, textureWidth * 4);
//	// Move texture pointer to next line
//	texturePnter += textureWidth * 4;
//	// Move screen pointer to next line
//	screenPnter += screenWidth * 4;
//}

void Window::blit(const Sprite & sprite) const
{
	Vector2i spritePosition = sprite.getPosition();
	BYTE* screenPointer = HAPI.GetScreenPointer() + (spritePosition.m_x + spritePosition.m_y * m_windowSize.m_x) * BYTES_PER_PIXEL;
	const BYTE* texture = sprite.getTexture().m_texture;

	for (int y = 0; y < sprite.getTexture().m_size.m_y; ++y)
	{
		memcpy(screenPointer, texture, sprite.getTexture().m_size.m_x * BYTES_PER_PIXEL);

		texture += sprite.getTexture().m_size.m_x * BYTES_PER_PIXEL;
		screenPointer += m_windowSize.m_x * BYTES_PER_PIXEL;
	}
}

//void Window::blit(const Sprite & sprite, float i) const
//{
//	BYTE* screen = HAPI.GetScreenPointer();
//	const BYTE* texture = sprite.getTexture().m_texture;
//	Vector2i textureSize = sprite.getTexture().m_size;
//
//	const int endOfLineScreenIncrement = (m_windowSize.m_x - textureSize.m_x) * 4;
//	for (int y = 0; y < textureSize.m_y; ++y)
//	{
//		for (int x = 0; x < textureSize.m_x * 4; x += 4)
//		{
//			const BYTE blue = texture[0];
//			const BYTE green = texture[1];
//			const BYTE red = texture[2];
//			const BYTE alpha = texture[3];
//			const float mod = alpha / i;
//			screen[0] = (BYTE)(mod*blue + (1.0f - mod) * screen[0]);
//			screen[1] = (BYTE)(mod*green + (1.0f - mod) * screen[1]);
//			screen[2] = (BYTE)(mod*red + (1.0f - mod) * screen[2]);
//		
//			screen += 4;
//			texture += 4;
//		}
//		screen += endOfLineScreenIncrement; 
//	}
//}

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

void Window::close()
{
	HAPI.Close();
}
