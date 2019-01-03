#pragma once

class Timer
{
public:
	Timer() {}

	bool isActive() const { return true; }
	bool isExpired() const { return true; }
	void reset() {}
	void update() {}
private:

};