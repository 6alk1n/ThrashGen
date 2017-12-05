//ThrashProject start file

#include <iostream>
#include <ctime>
#include "GameScreen.h"
#undef main
using namespace ThrashEngine;

int SDL_main(int argc, char* argv[]) //SDL_main instead of basic main
{
	srand(time(NULL));
	InitEngine();
	if (_CoreState != EngineState::Ok)
	{
		std::cout << "Engine initialization error" << std::endl;
	}
	else
	{
		std::cout << "Engine initializated succesfull" << std::endl;
	}
	/*
	std::cout << "size of int " << sizeof(int) << std::endl;
	std::cout << "size of double " << sizeof(double) << std::endl;
	std::cout << "size of bool " << sizeof(bool) << std::endl;
	std::cout << "size of char " << sizeof(char) << std::endl;
	std::cout << "size of float " << sizeof(float) << std::endl;
	std::cout << "size of rectangle " << sizeof(ThrashEngine::Rectangle) << std::endl;
	std::cout << "size of vector " << sizeof(ThrashEngine::Vector) << std::endl;
	*/

	SystemNodeList = new SystemNode;
	SystemNodeList->next = nullptr;
	SystemNodeList->sys = nullptr;
	
	GameScreen App;
	App.Create();

//	ThrashEngine::SystemList.push_back((System*)&App);
	//App.GetWindow()->SetScreenSize(1024, 768);
	App.GetWindow()->SetScreenName(std::string("Platform"));
	if (App.Init() != ResultState::Success)
	{
		int a;
		a = 1;
	}
	App.GetWindow()->SetScreenPosition(10, 10);
	System* sys = (System*)(&App);
	App.SystemList.push_back(sys);
	//ThrashEngine::SystemList.push_back((System*)(App.m_graphics));
	App.Run();
	App.Shutdown();
	KillEngine();
	system("Pause");

	return 0;
}