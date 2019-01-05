#pragma once

class Timer
{
public:
	Timer();

	bool isActive() const;
	bool isExpired() const;
	void reset();
	void update(float deltaTime);


	float m_time;
};