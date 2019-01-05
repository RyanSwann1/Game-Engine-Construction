#include "Rectangle.h"
#include <algorithm>
#include <iostream>

Rectangle::Rectangle(int x, int y, int width, int height)
	: m_x(x),
	m_y(y),
	m_width(width),
	m_height(height)
{}

int Rectangle::getWidth() const
{
	return m_width;
}

int Rectangle::getHeight() const
{
	return m_height;
}

void Rectangle::clipTo(const Rectangle & other)
{
	//Left Check
	if (m_x < other.m_x)
	{
		m_x = other.m_x;
	}
	if (m_width < other.m_x)
	{
		m_width = other.m_x;
	}

	//Right Check
	if (m_width > other.m_width)
	{
		m_width = other.m_width;
	}
	if (m_x > other.m_width)
	{
		m_x = other.m_width;
	}
	
	//Top Check
	if (m_y < other.m_y)
	{
		m_y = other.m_y;
	}
	if (m_height < other.m_y)
	{
		m_height = other.m_y;
	}

	//Bottom Check
	if (m_y > other.m_height)
	{
		m_y = other.m_height;
	}
	if (m_height > other.m_height)
	{
		m_height = other.m_height;
	}
}

void Rectangle::translate(int x, int y)
{
	m_x += x;
	m_width += x;
	m_y += y;
	m_height += y;
}

void Rectangle::print()
{
	std::cout << "Left: " << m_x << "\n";
	std::cout << "Right: " << m_width << "\n";
	std::cout << "Top: " << m_y << "\n";
	std::cout << "Bottom: " << m_height << "\n";
}
