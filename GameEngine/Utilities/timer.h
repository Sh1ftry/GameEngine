#pragma once
#include <chrono>

class Timer
{
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> _start;
public:
	Timer()
	{
		restart();
	}

	void restart()
	{
		_start = std::chrono::high_resolution_clock::now();
	}

	std::chrono::duration<double> time() const
	{
		return std::chrono::high_resolution_clock::now() - _start;
	}

};