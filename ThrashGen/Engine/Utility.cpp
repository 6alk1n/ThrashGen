#include "Utility.hpp"

#include <iostream>

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>

namespace ThrashEngine
{
	std::string Utility::DialogOpenFile(char* title, char* filter, long flags=0)
	{
		char filename[MAX_PATH];

		OPENFILENAMEA ofn;
		ZeroMemory(&filename, sizeof(filename));
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
		ofn.lpstrFilter = filter;
		ofn.lpstrFile = filename;
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrTitle = title;
		if (!flags)
			ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;
		else 
			ofn.Flags = flags;

		if (GetOpenFileNameA(&ofn))
		{
			std::cout << "You chose the file \"" << filename << "\"\n";
		}
		return filename;
	}

	std::string Utility::DialogSaveFile(char* title, char* filter, long flags)
	{
		char filename[MAX_PATH];

		OPENFILENAMEA ofn;
		ZeroMemory(&filename, sizeof(filename));
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
	//	if (!filter.size())
	//		ofn.lpstrFilter = "Text Files\0*.txt\0Any File\0*.*\0";
	//	else
			ofn.lpstrFilter = filter;
		ofn.lpstrFile = filename;
		ofn.nMaxFile = MAX_PATH;
	//	if (!title.size())
		//	ofn.lpstrTitle = "Select a File, yo!";
	//	else
			ofn.lpstrTitle = title;
		if (!flags)
			ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;
		else
			ofn.Flags = flags;
		//ofn.
		if (GetSaveFileNameA(&ofn))
		{
			std::cout << "You chose the file \"" << filename << "\"\n";
		}
		return filename;
	}
	std::list<std::string> Utility::ParseString(std::string str)
	{
		std::list<std::string> result;
		int start=0, end=0;
		for (auto i = str.begin(); i != str.end(); )
		{
			while (i != str.end() &&  *i == ' ' )
			{
				i++;
				start++;
			}
			end = start;
			while (i != str.end() && *i != ' ' )
			{
				i++;
				end++;
			}
			if(end>start)
			result.push_back(str.substr(start,end-start));
			start = end;
		}
		return result;
	}
	unsigned int Utility::CheckSum(std::string filePath)
	{
		std::ifstream file;
		file.open(filePath.c_str(), std::ios::in | std::ios::binary);
		if (file) {
			uint32_t sum = 0;

			uint32_t word = 0;
			while (file.read(reinterpret_cast<char*>(&word), sizeof(word))) {
				sum += word;
				word = 0;
			}

			sum += word; // add the last word, could be 0
						 // if the file size is divisible by 4

			return sum;
		}
		return 0;
	}
	std::string Utility::NumToHex(unsigned int num)
	{
		char* converttable = "0123456789abcdef";
		std::string result = "";
		while (num)
		{
			
			result += converttable[num&15];
			num = num >> 4;
		}
		while (result.size() < 8)
		{
			result.push_back('0');
		}
		return result;
	}
}