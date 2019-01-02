#pragma once

struct Vector2i
{
public:
	Vector2i(int x = 0, int y = 0)
		: m_x(x),
		m_y(y)
	{}

	Vector2i operator+=(Vector2i v)
	{
		return Vector2i(m_x + v.m_x, m_y + v.m_y);
	}

	int m_x;
	int m_y;
};