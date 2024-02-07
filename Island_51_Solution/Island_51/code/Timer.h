#pragma once
#include <chrono>
class Timer
{
public:
	Timer() {
		_start_time = _current_time = _last_delta_tick = std::chrono::system_clock::now();
		_delta_time = std::chrono::duration<float>(0);
	}

	void RestartTimer()
	{
		_start_time = std::chrono::system_clock::now();
	}

	float GetDeltaTime()
	{
		//Setting the current time to now
		_current_time = std::chrono::system_clock::now();

		//Getting Duration Since Last Delta Tick
		_delta_time = _current_time - _last_delta_tick;

		//Getting new value for last delta tick
		_last_delta_tick = std::chrono::system_clock::now();

		return _delta_time.count();
	}

	float GetElapsedTime()
	{
		_current_time = std::chrono::system_clock::now();
		std::chrono::duration<float> _elapsed_time = _current_time - _start_time;
		return _elapsed_time.count();
	}


private:
	std::chrono::system_clock::time_point _start_time, _current_time, _last_delta_tick;
	std::chrono::duration<float> _delta_time;
};