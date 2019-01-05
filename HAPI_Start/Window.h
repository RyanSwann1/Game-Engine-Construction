#pragma once

#include <string>
#include "Vector2i.h"
#include <HAPI_lib.h>

constexpr auto BYTES_PER_PIXEL = 4;

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
	Window&& operator=(Window&&) = delete;

	unsigned int getOffSet(Vector2f position) const;
	unsigned int getOffSet(Vector3f position) const;
	unsigned int getOffSet(Vector2i position) const;
	HAPISPACE::BYTE* getScreen() const;
	Vector2i getSize();

	void draw(const Sprite& sprite, Vector2i pos) const;

	void clearScreenToBlack() const;

private:
	const Vector2i m_windowSize;
};