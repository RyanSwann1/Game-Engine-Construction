#pragma once

#include <string>
#include "Vector2i.h"
#include <HAPI_lib.h>

constexpr auto BYTES_PER_PIXEL = 4;
using namespace HAPISPACE;

struct Vector2f;
struct Vector3f;
class Sprite;
class Window
{
public:
	Window(Vector2i size);
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator=(Window&&) = delete;

	unsigned int getOffSet(Vector2f position) const;
	unsigned int getOffSet(Vector3f position) const;
	unsigned int getOffSet(Vector2i position) const;
	int getEyeDistance() const;
	BYTE* getScreen() const;
	Vector2i getSize();

	void blit(const Sprite& sprite) const;
	//void blit(const Sprite& sprite, float i) const;

	void clearScreenToBlack() const;
	void clearScreenToGrey() const;
	void close();

private:
	const Vector2i m_windowSize;
	const int m_maxEyeDistance;
	const int m_minEyeDistance;
	int m_eyeDistance;
	bool m_isOpen;

	
};