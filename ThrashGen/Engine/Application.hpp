#pragma once
#include "Core.hpp"
#include "Window.hpp"
#include "Input.hpp"
#include "Graphics.hpp"
#include "AudioMaster.hpp"
#include "Monitoring.hpp"

#include "Parameters.hpp"
#include "System.hpp"
/*
Applcation class. Main game object. It loops all process. 
Further application must be inherited from this class to start process

*/



namespace ThrashEngine
{


	class Application:System
	{
	public:
		Application();
		~Application();

		virtual ResultState Create(); //Allocates memory for subsystem
		virtual ResultState Init(); //Initializes all subsystems
		virtual ResultState Run();  //Start main loop
		virtual ResultState Shutdown(); //Free memory from subsystems
		void SetProperties();

		//virtual functions for overriding
		virtual ResultState Draw()=0;
		virtual ResultState Update()=0;
		virtual ResultState OnInit()=0;
		virtual ResultState OnShutdown()=0;

		Window* GetWindow(); 
		virtual EngineState Restart(std::list<PropertyClass*>);

	public:
		Window* m_window; //window pointer
		EngineState m_state; //specifies the current state of all system
		bool m_done; //main loop continue variable
		Input* m_input; //input pointer
		Graphics* m_graphics; //graphics (renderer) pointer
		AudioMaster* m_audio; // Audio system(sound)
		Monitoring m_monitor; // Resource (memory,cpu) manager,viewer
		unsigned int m_fps;
		PropertyClass  AppParams;
		std::vector<System*> SystemList;
	};
	static std::vector<System*>* SystemListPtr;
}