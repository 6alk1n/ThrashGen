#include "Monitoring.hpp"

namespace ThrashEngine
{
	Monitoring::Monitoring()
	{
		m_submonitorArray = 10;
	}
	Monitoring::~Monitoring()
	{

	}
	int Monitoring::StartMonitor(std::string name)
	{
		bool found = false;
		for (auto i = m_monitors.begin(); i != m_monitors.end(); i++)
		{
			if (i->MonitorName == name)
			{
				found = true;
				break;
			}
		}
		if (!found) {
			Monitor newMonitor;
			newMonitor.MonitorName = name;
			newMonitor.diffTime = 0;
			m_monitors.push_back(newMonitor);
		}
		for (auto i = m_monitors.begin(); i != m_monitors.end(); i++)
		{
			if (i->MonitorName == name)
			{
				if (i->m_subtimers.size() < m_submonitorArray)
				{
				//	if (i->m_subtimers.capacity())
				//		(i->m_subtimers)[i->m_subtimers.capacity()-1].End();
					Timer newTimer;
					newTimer.Start();
					i->m_subtimers.push_back(newTimer);
				}
				else
				{
				//	if (i->m_subtimers.capacity())
				//		(i->m_subtimers)[i->m_subtimers.capacity() - 1].End();

					double diff=0;
					for (auto n = i->m_subtimers.begin(); n != i->m_subtimers.end(); n++)
						diff += n->GetTime();
					i->diffTime = diff/m_submonitorArray;
					i->m_subtimers.clear();
				}
				//i->timer.Start();
				return 1;
			}
		}
		return 2;
	}
	int Monitoring::EndMonitor(std::string name)
	{
		for (auto i = m_monitors.begin(); i != m_monitors.end(); i++)
		{
			if (i->MonitorName == name)
			{
				if (i->m_subtimers.size())
					(i->m_subtimers)[i->m_subtimers.size() - 1].End();

				return 1;
			}
		}
		return 0;
	}

	std::vector<Monitor>* Monitoring::GetMonitors()
	{
		return &m_monitors;
	}
	Monitor Monitoring::GetMonitor(std::string name)
	{
		for (auto i = m_monitors.begin(); i != m_monitors.end(); i++)
		{
			if (i->MonitorName == name)
			{
				return *i;
			}
		}
		return Monitor();
	}
	void Monitoring::SetSubMonitorArray(int sub)
	{
		m_submonitorArray = sub;
	}
}