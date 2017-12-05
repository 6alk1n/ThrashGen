/******************************
//Core.hpp basic engine interface

---Core info---
Current version - 0.2
Date(d,m,y)		- 07.06.2017
Version Name 	- ThrashEngine v 0.2 

*******************************/

#ifdef WIN32
#include<Windows.h>
#endif

#pragma once
#include <SDL.h>
//include math types
#include "Types.hpp"

//probably not cross-platform
#include <iostream>
#include <fstream>

#define CORE_INIT

//Macros for defining ansi and unicode as one type tchar
//For wide char strings use tchar instead of wchar or char!
#ifdef _UNICODE
  //Define tchar as wchar
	typedef wchar_t tchar;
	#define _T(x) L ##x

#else
  //Define tchar as char
	typedef char tchar;
	#define _T(x) x

#endif

//For error boxes and some messaging
#include "Log.hpp"

//Enum for engine state initialization result

namespace ThrashEngine {

	//Used for specifing engine and subsystems state
	enum EngineState
	{
		Invalid,
		Ok,
		Failed,
		Shutdown,
		Created
	};
	//Instead of int or bool. Enumeration type for results
	enum ResultState
	{
		Default,
		Success,
		Fail
	};

	static EngineState _CoreState = EngineState::Invalid; //Global Engine and status state
	static const char* EngineVersion = "0.2c";	   //Version of Engine
	static const char* EngineVersionState = "alpha"; //State Version of Engine

	//Init SDL stuff
	static EngineState InitEngine()
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0) // Init SDL video 
		{
			//failed to init
			_CoreState = EngineState::Failed;
#ifdef NDEBUG
			ErrorBox(_T("Failed to Init Engine!"), _T("Error Init Engine"));
#endif
			std::cout << SDL_GetError();
		}
		else
		{
			//all initialized well
#ifdef NDEBUG
			ErrorBox(_T("Engine inited successfully!"), _T("Init successfully"));
#endif
			_CoreState = EngineState::Ok;
			std::cout << "===Thrashengine " << EngineVersion << " " << EngineVersionState << "===" << std::endl;
		}
		return _CoreState;
	}
	//Call SDL_Quit and set CoreState to shutdown
	static EngineState KillEngine()
	{
		SDL_Quit();
		_CoreState = EngineState::Shutdown;
		return _CoreState;
	}
	static bool is_file_exist(const char *fileName)
	{
		std::ifstream infile(fileName); //check with ifstream
		return infile.good();
	}

}