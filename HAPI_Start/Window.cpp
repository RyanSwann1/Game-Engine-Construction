#include "Window.h"
#include <utility>
#include <cassert>
#include "Vector2f.h"
#include "Vector3f.h"
#include "Utilities.h"
#include "Sprite.h"
#include "Texture.h"

Window::Window(Vector2i size)
	: m_windowSize(size)
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
//Rectangle sourceRect(0, 64, 0, 64);
//Rectangle destinationRect(0, 800, 0, 600);
//Vector2i position(880, 400);
//
////When blitting makes sure height & width == positive
//
//sourceRect.translate(position.m_x, position.m_y);
////Right == 780 + 64
////top == 400 + 64
//sourceRect.clipTo(destinationRect);
////Right = destinationRect.x
////sourceRect.print();
//sourceRect.translate(-position.m_x, -position.m_y);
//sourceRect.print();
// Rectangle newSource(0,frame.Width(),0,frame.Height())

void Window::draw(const Sprite & sprite, Vector2i position) const
{
	//Top left of the object
	BYTE* screenPointer = HAPI.GetScreenPointer() + (position.m_x + position.m_y * m_windowSize.m_x) * BYTES_PER_PIXEL;
	
	//Points to the top left of the texture
	const BYTE* texture = sprite.getTexture().m_texture;
	const auto& rect = sprite.m_rect; 

	//Screen rect
	Rectangle destinationRect(0, 0, m_windowSize.m_x, m_windowSize.m_y);
	//Move sprite rect to screen space
	Rectangle sourceRect(0, 0, rect.getWidth(), rect.getHeight());
	sourceRect.translate(position.m_x, position.m_y);
	//Clip sprite rect to screen space
	sourceRect.clipTo(destinationRect);
	//Find out how big clipped sprite rect is 
	sourceRect.translate(-position.m_x, -position.m_y);
	//If clipped sprite is invalid, do not blit
	if (sourceRect.getWidth() == 0 || sourceRect.getHeight() == 0)
	{
		return;
	}

	//Top left of the Sprite - Rect == top left of the sprite in the texture
	const BYTE* spritePointer = texture + (rect.m_x + rect.m_y * sprite.getTexture().m_size.m_x) * BYTES_PER_PIXEL;

	//Draw the clipped rect
	for (int y = sourceRect.m_y; y < sourceRect.m_height; ++y)
	{
		//Beginning Pointer of the current row of the clipped rect
		//IE -- Where it is on the screen
		BYTE* screenPointerRow = screenPointer + (sourceRect.m_x + y * m_windowSize.m_x) * BYTES_PER_PIXEL;

		//Do same for sprite - do not draw the areas that have been clipped. 
		//Start at beginning of the row
		const BYTE* spritePointerRow = spritePointer + (sourceRect.m_x + y * sprite.getTexture().m_size.m_x) * BYTES_PER_PIXEL;

		//Draw block of memory
		memcpy(screenPointerRow, spritePointerRow, sourceRect.getWidth() * BYTES_PER_PIXEL);
	}


	//for (int y = 0; y < sprite.getTexture().m_size.m_y; ++y)
	//{
	//	memcpy(screenPointer, texture, sprite.getTexture().m_size.m_x * BYTES_PER_PIXEL);
	//	texture += sprite.getTexture().m_size.m_x * BYTES_PER_PIXEL;
	//	screenPointer += m_windowSize.m_x * BYTES_PER_PIXEL;
	//}
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