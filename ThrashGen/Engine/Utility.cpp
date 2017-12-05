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

}