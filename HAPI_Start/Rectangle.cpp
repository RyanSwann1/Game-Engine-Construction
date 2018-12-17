#include "Rectangle.h"
#include <algorithm>

Rectangle::Rectangle(int left, int right, int top, int bottom)
{
}

void Rectangle::add(int right, int bottom)
{
}

int Rectangle::getWidth() const
{
	return 0;
}

int Rectangle::getHeight() const
{
	return 0;
}

void Rectangle::clipTo(const Rectangle & other)
{
	if (m_left < other.m_left)
	{
		m_left = other.m_left;
	}
	else if (m_right > other.m_right)
	{
		m_right = other.m_right;
	}
	else if (m_top < other.m_top)
	{
		m_top = other.m_top;
	}
	else if (m_bottom > other.m_bottom)
	{
		m_bottom = other.m_bottom;
	}
}
