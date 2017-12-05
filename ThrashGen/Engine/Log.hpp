#pragma once
/******************************
//Log.hpp logging and messaging

ErrorBox - throws messagebox with ok button
*******************************/
#include "Core.hpp"
//WIN32 macro because on other systems there is no MessageBox 
//WINDOWS ONLY!!!
#ifdef WIN32 
namespace ThrashEngine {

	static int ErrorBox(tchar* title, tchar* msg) //Throws a box with ok button
	{
		return MessageBox(
			NULL,
			title,
			msg,
			MB_OK
		);
	}
}
#endif
