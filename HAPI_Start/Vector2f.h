#pragma once

struct Vector2f
{
	Vector2f(float x = 0, float y = 0)
		: m_x(x),
		m_y(y)
	{}

	float m_x;
	float m_y;
};