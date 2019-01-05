#include "Timer.h"

Timer::Timer(float expirationTime)
	: m_elaspedTime(0),
	m_expirationTime(expirationTime)
{}

bool Timer::isActive() const
{
	return false;
}

bool Timer::isExpired() const
{
	return (m_elaspedTime >= m_expirationTime);
}

void Timer::reset()
{
	m_elaspedTime = 0;
}

void Timer::update(float deltaTime)
{
	m_elaspedTime += deltaTime;
}