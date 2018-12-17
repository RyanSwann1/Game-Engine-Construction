#pragma once

#include "Vector2i.h"

class Rectangle
{
public:
	Rectangle(int left, int right, int top, int bottom);

	void add(int right, int bottom);
	int getWidth() const;
	int getHeight() const;

	void clipTo(const Rectangle& other);

private:
	int m_left;
	int m_right;
	int m_top;
	int m_bottom;
};

