#include "ConsoleCommands.hpp"
#include <Engine/Utility.hpp>
#include <Engine/Application.hpp>
int HandleConsoleCommand(GameScreen* screen, std::string* console_text)
{
	std::list<std::string> l;
	std::list<std::string> parse = Utility::ParseString(*console_text);
	if (parse.size() == 1)											//One word commands
	{
		auto i = parse.begin();
		if (*i == "exit")				//exit (Shutdown)
		{
			screen->OnShutdown();
		}
		else if (*i == "info")			//info (Get general info)
		{
			std::string enginestr = (screen->AppParams).Get("engine")->value;
			screen->m_console.WriteLine(enginestr);
		}
		else if (*i == "clear")			//clear (Clear console)
		{
			screen->m_console.Clear();
		}
		else if (*i == "help")
		{
			screen->m_console.WriteLine("info - Get info about engine");
			screen->m_console.WriteLine("exit - Shutdown the project");
			screen->m_console.WriteLine("clear - Clear console");
			screen->m_console.WriteLine("set(paramGroup) (paramName) (paramValue) - Set already exsisting App(global) property to some value in paramGroup(paramGroup only system)");
			screen->m_console.WriteLine("get(paramGroup) (paramName) - Get param value on console(From system) from paramGroup");
			screen->m_console.WriteLine("restart(systemName) - Restart(reload) some part of system(graphics, textures, sound e.t.c)");
			screen->m_console.WriteLine("*setnew(paramName) (paramValue) (#paramtype) - Add new param to App properties");
			screen->m_console.WriteLine("*help - See help(all commands)");
			screen->m_console.WriteLine("get(paramGroup) - Get all param names");
		}
		else
		{
			screen->m_console.WriteLine("\'" + *console_text + "\'" + " - Unknown command");
		}
	}
	else if (parse.size() == 2)
	{
		auto i = parse.begin();
		if (*i == "restart")
		{
			auto paramName = i;
			paramName++;


			System* system = nullptr;

			//if (system)
			{

				std::list<Property*> property;

			/*	if (*paramName == "window") {
					property.push_back(screen->AppParams.GetProperty("width"));
					property.push_back(screen->AppParams.GetProperty("height"));
					screen->m_window->ResizeWindow(*(double*)(w->data), *(double*)(h->data));
				}*/
				//	screen->m_window->Restart(property);
				//	property.push_back(screen->AppParams.GetProperty("vsync"));
				//}

			//	system->Restart(property);
			}

			if (*paramName == "graphics")
			{
				ThrashEngine::Property* w = screen->AppParams.Get("width");
				ThrashEngine::Property* h = screen->AppParams.Get("height");
				ThrashEngine::Property* vsync = screen->AppParams.Get("vsync");
				ThrashEngine::Property* debug = screen->AppParams.Get("debugmode");
				screen->m_window->ResizeWindow(StrToDouble(w->value), StrToDouble(h->value));
				screen->m_window->SetVsync(StrToDouble(vsync->value));
				screen->m_graphics->SetVsync(StrToDouble(vsync->value));
				screen->m_world->m_property.Set("Debug",(StrToDouble(debug->value)));
			}
			else if (*paramName == "system")
			{
				ThrashEngine::Property*title = screen->AppParams.Get("title");
				screen->m_window->SetScreenName(title->value);
				ThrashEngine::Property*posx = screen->AppParams.Get("posx");
				ThrashEngine::Property*posy = screen->AppParams.Get("posy");
				screen->m_window->SetScreenPosition(StrToDouble(posx->value), StrToDouble(posy->value));
			}
			else if (*paramName == "sound")
			{
				double vol = screen->AppParams.GetDouble("mastervolume");
				screen->m_soundManager->SetVolumeAll(vol);
			}
			else if (*paramName == "all")
			{
				ThrashEngine::Property* w = screen->AppParams.Get("width");
				ThrashEngine::Property* h = screen->AppParams.Get("height");
				ThrashEngine::Property* vsync = screen->AppParams.Get("vsync");
				ThrashEngine::Property* debug = screen->AppParams.Get("debugmode");
				screen->m_window->ResizeWindow(StrToDouble(w->value), StrToDouble(h->value));
				screen->m_window->SetVsync(StrToDouble(vsync->value));
				screen->m_graphics->SetVsync(StrToDouble(vsync->value));
				screen->m_world->m_property.Set("Debug",(StrToDouble(debug->value)));
				ThrashEngine::Property*title = screen->AppParams.Get("title");
				screen->m_window->SetScreenName((title->value));
				ThrashEngine::Property*posx = screen->AppParams.Get("posx");
				ThrashEngine::Property*posy = screen->AppParams.Get("posy");
				screen->m_window->SetScreenPosition(StrToDouble(posx->value), StrToDouble(posy->value));
				double vol = StrToDouble(screen->AppParams.Get("mastervolume")->value);
				screen->m_soundManager->SetVolumeAll(vol);
			}
		}
		else if (*i == "get")
		{
			auto groupName = i;
			groupName++;

			if (*groupName == "system")
			{
				/*
				for (auto i = screen->AppParams.m_property.begin(); i != screen->AppParams.m_property.end(); i++)
				{
					std::string str = i->first;
					if (i->second.name)
					{
						str += " - " + *i->second.name;
					}
					screen->m_console.WriteLine(str);
				}*/
			}

		}
	}
	else if (parse.size() == 3)
	{
		auto i = parse.begin();
		if (*i == "get")
		{
			auto groupName = i;
			groupName++;

			if (*groupName == "system")
			{
				auto paramName = groupName;
				paramName++;
				ThrashEngine::Property* propgetter = screen->AppParams.Get(*paramName);
				if (propgetter) {
					if (propgetter->type == STRING)
					{
						screen->m_console.WriteLine(propgetter->value);
					}
					else
					{
						double val = StrToDouble(propgetter->value);
						screen->m_console.WriteLine(DoubleToStr(val));
					}
				}
				else
				{
					screen->m_console.WriteLine(*paramName + " - Unknown property");
				}
				//if(*paramName==)
			}
		}
	}
	else if (parse.size() >= 4)									//Four word commands
	{
		auto i = parse.begin();
		if (*i == "set")				//set (Set property)
		{
			auto paramName = i;
			paramName++;

			if (*paramName == "system") {

				paramName++;

				ThrashEngine::Property* prop = screen->AppParams.Get(*paramName);
				if (screen->AppParams.status)
				{
					auto value = paramName;
					value++;
					if (parse.size() > 4)
					{
						std::string longvalue = *value; 
						longvalue.clear();
						
						for (auto n = value++; n != parse.end(); n++)
						{							
							longvalue += *n;
							longvalue += ' ';
						}
						screen->AppParams.Set(*paramName, longvalue);
						longvalue.clear();
					}
					else {
						if (prop->type == ThrashEngine::STRING)
						{
							screen->AppParams.Set(*paramName, *value);
							/*	delete prop->data;
							std::string* str= new std::string;
							str = (std::string*)&(*value);
							prop->data = str;*/
						}
						else if (prop->type == ThrashEngine::DOUBLE)
						{
							double val = ThrashEngine::StrToDouble(*value);
							screen->AppParams.Set(*paramName, val);
						}			
					}
				}
				else
				{
					screen->m_console.WriteLine("\'" + *paramName + "\'" + " - Unknown property");
				}
			}
			else
			{
				screen->m_console.WriteLine("\'" + *paramName + "\'" + " - Unknown group");
			}
		}

	}
	else
	{
		screen->m_console.WriteLine("\'" + *console_text + "\'" + " - Unknown command");
	}
	/*for (auto i = parse.begin(); i != parse.end(); i++)
	{
	std::cout << *i << std::endl;
	}*/
	return 1;
}