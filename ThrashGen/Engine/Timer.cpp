#include "Timer.hpp"
namespace ThrashEngine {
	Timer::Timer()
	{
		m_startTicks = m_endTicks = 0;
		m_freq = SDL_GetPerformanceFrequency();
	}
	Timer::~Timer()
	{

	}

	void Timer::Start()
	{
		m_startTicks = SDL_GetPerformanceCounter();
		
	}
	Uint64 Timer::End()
	{
		if (m_startTicks == 0) return 0;
		m_endTicks = SDL_GetPerformanceCounter();
		m_diff = double(m_endTicks - m_startTicks) / double(m_freq);
		m_startTicks = m_endTicks;
		return m_diff;
	}
	double Timer::GetTime()
	{
		return m_diff;
	}
}