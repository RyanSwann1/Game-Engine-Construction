#pragma once

struct Vector3f
{
	Vector3f(float x = 0, float y = 0, float z = 0)
		: m_x(x),
		m_y(y),
		m_z(z)
	{}

	Vector3f& operator+=(const Vector3f& v)
	{
		m_x = v.m_x;
		m_y = v.m_y;
		m_z = v.m_z;

		return *this;
	}

	Vector3f operator+(const Vector3f& v) const
	{
		return Vector3f(m_x + v.m_x, m_y + v.m_y, m_z + v.m_z);
	}

	bool operator==(const Vector3f& v) const
	{
		return (m_x == v.m_x && m_y == v.m_y && m_z == v.m_z);
	}

	bool operator!=(const Vector3f& v) const
	{
		return (m_x == v.m_x && m_y == v.m_y && m_z == v.m_z);
	}

	float m_x;
	float m_y;
	float m_z;
};