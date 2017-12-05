#pragma once
#include "Core.hpp"
#include <list>
namespace ThrashEngine
{
	class Utility
	{
	public:
		static std::string DialogOpenFile(char* title, char* filter,long flags);
		static std::string DialogSaveFile(char* title, char* filter, long flags);
		static std::list<std::string> ParseString(std::string);
		static unsigned int CheckSum(std::string filePath);
		static std::string NumToHex(unsigned int);
	protected:
	};


}