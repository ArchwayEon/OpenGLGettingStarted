#include "HighResolutionTimer.h"

HighResolutionTimer::HighResolutionTimer()
{
	StartTiming();
}

void HighResolutionTimer::StartTiming()
{
	m_start = std::chrono::high_resolution_clock::now();
}

double HighResolutionTimer::GetElapsedTimeInSeconds()
{
	m_end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> timeSpan =
		std::chrono::duration_cast<std::chrono::duration<double>>(m_end - m_start);
	m_start = std::chrono::high_resolution_clock::now();
	return timeSpan.count();
}
