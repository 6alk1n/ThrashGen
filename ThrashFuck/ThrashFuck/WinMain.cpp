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

	GameScreen App;
	App.Create();
	App.GetWindow()->SetScreenSize(1024, 768);
	App.GetWindow()->SetScreenName(std::string("SUPERGAY"));
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