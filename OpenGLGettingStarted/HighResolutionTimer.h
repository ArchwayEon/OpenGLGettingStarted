#pragma once
#include <ctime>
#include <ratio>
#include <chrono>
class HighResolutionTimer
{
protected:
	std::chrono::high_resolution_clock::time_point m_start, m_end;

public:
	HighResolutionTimer();
	void StartTiming();
	double GetElapsedTimeInSeconds();
};

