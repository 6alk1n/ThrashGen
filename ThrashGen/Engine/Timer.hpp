#pragma once
#include "Core.hpp"
namespace ThrashEngine {
	class Timer
	{
	public:
		Timer();
		~Timer();
		void Start();
		Uint64 End();
		double GetTime();
	protected:
		Uint64 m_startTicks;
		Uint64 m_endTicks;
		double m_diff;
		Uint64 m_freq;
	};
}