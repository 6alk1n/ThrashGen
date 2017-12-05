#pragma once
/*************
Window class
*****************/
#include <SDL.h>

#include "Core.hpp"
#include <string>
#include "System.hpp"

namespace ThrashEngine {

	class Window:System
	{
	public:
		Window();  //default constructor
		~Window(); //default destructor
		EngineState GetState(); //return the state of the window
		ResultState Init(unsigned int width,unsigned int height,std::string name); //Creates window and surface with parameters
		ResultState Init(); //Creates window and surface 
		ResultState Shutdown(); //Destroys window and free memory

		ResultState SetScreenSize(unsigned int width, unsigned int height); //Sets size before init
		ResultState SetScreenName(std::string);//Sets name before init

		ResultState SetScreenPosition(unsigned int x, unsigned int y); //Set window position

		SDL_Surface* GetSurface();	//Get ScreenSurface
		SDL_Window* GetWindow();	//Get SDL object of window
		ResultState ResizeWindow(unsigned int width, unsigned int height); //Resize already created window
		ResultState SetVsync(bool);

		unsigned int GetScreenWidth();
		unsigned int GetScreenHeight();


		virtual EngineState Restart(std::list<PropertyClass*>);
		
	protected:

		SDL_Window* m_Window; //Window and handler on it

		SDL_Surface* m_ScreenSurface; //Window screen surface

		EngineState m_WindowState; //Window system state;

		//Screen Size
		unsigned int m_ScreenWidth;
		unsigned int m_ScreenHeight;

		//Screen Position
		unsigned int m_ScreenPosX;
		unsigned int m_ScreenPosY;

		std::string m_WindowName; //Window name

	};
}