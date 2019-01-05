#include "Timer.h"

Timer::Timer()
	: m_time(0)
{
}

bool Timer::isActive() const
{
	return false;
}

bool Timer::isExpired() const
{
	return false;
}

void Timer::reset()
{
	m_time = 0;
}

void Timer::update(float deltaTime)
{
	m_time += deltaTime;
}
