#pragma once

#include "Vector2i.h"

class Rectangle
{
public:
	Rectangle(int x = 0, int y = 0, int width = 0, int height = 0);

	int getWidth() const;
	int getHeight() const;

	void clipTo(const Rectangle& other);
	void translate(int x, int y);
	void print();

	int m_x;
	int m_width;
	int m_y;
	int m_height;
};