#pragma once
#include <chrono>


/**
 * @brief Class responsible for measuring time
 */
class Timer
{
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> _start;
public:
	/**
	 * @brief Starts the timer
	 */
	Timer()
	{
		restart();
	}

	/**
	 * @brief Restarts the timer
	 */
	void restart()
	{
		_start = std::chrono::high_resolution_clock::now();
	}

	/**
	 * @return Duration since the start if the timer
	 */
	std::chrono::duration<float> time() const
	{
		return std::chrono::high_resolution_clock::now() - _start;
	}

};