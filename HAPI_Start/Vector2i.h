#pragma once

struct Vector2i
{
public:
	Vector2i(int x = 0, int y = 0)
		: m_x(x),
		m_y(y)
	{}

	int m_x;
	int m_y;
};