#pragma once
#include "Timer.hpp"
#include <vector>
#include <string>



namespace ThrashEngine {

	struct Monitor
	{
		std::vector<Timer> m_subtimers;
		double diffTime;
		std::string MonitorName;
	};

	class Monitoring
	{
	public:
		Monitoring();
		~Monitoring();
		int StartMonitor(std::string);
		int EndMonitor(std::string);
		std::vector<Monitor>* GetMonitors();
		Monitor GetMonitor(std::string);
		void SetSubMonitorArray(int);
	protected:
		std::vector<Monitor> m_monitors;
		int m_submonitorArray;
	};
}