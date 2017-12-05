#pragma once
#include "Parameters.hpp"
#include <list>
#include <vector>
namespace ThrashEngine {

	class System
	{
	public:
		virtual EngineState Restart(std::list<PropertyClass*>) = 0;
		std::string m_SystemName;
	};

	struct SystemNode
	{
		System* sys;
		SystemNode* next;
	} static *SystemNodeList;

}