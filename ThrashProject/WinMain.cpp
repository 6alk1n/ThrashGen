//ThrashProject start file

#include <Engine/Core.hpp> //Include Core. Init Engine
#include <Engine/Window.hpp> //Include window
#include <Engine/Application.hpp> //Include Application
#include <iostream>
#include "Game.hpp"
#include <ctime>
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

	Game App;
	App.Create();
	App.GetWindow()->SetScreenSize(800, 600);
	App.GetWindow()->SetScreenName(std::string("Thrash"));
	if (App.Init() != ResultState::Success)
	{
		int a;
		a = 1;
	}
	App.GetWindow()->SetScreenPosition(100, 100);
	App.Run();
	App.Shutdown();
	KillEngine();
	system("Pause");

	return 0;
}