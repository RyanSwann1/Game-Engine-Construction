#pragma once

class Timer
{
public:
	Timer(float expirationTime = 0);

	bool isActive() const;
	bool isExpired() const;
	void reset();
	void update(float deltaTime);

private:
	float m_elaspedTime;
	float m_expirationTime;
};