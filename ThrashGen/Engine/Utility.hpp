#pragma once
#include "Core.hpp"

namespace ThrashEngine
{
	class Utility
	{
	public:
		static std::string DialogOpenFile(char* title, char* filter,long flags);
		static std::string DialogSaveFile(char* title, char* filter, long flags);
	protected:
	
	};


}