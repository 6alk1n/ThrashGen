#include "Window.hpp"

namespace ThrashEngine
{
	Window::Window()
	{
		m_Window = nullptr; //Set to null values
		m_ScreenSurface = nullptr;
		m_WindowState = EngineState::Invalid;
		m_ScreenHeight = 0;
		m_ScreenWidth = 0;
	}
	Window::~Window()
	{
		Shutdown();
		//empty
	}
	EngineState Window::GetState()
	{
		return m_WindowState;
	}
	ResultState Window::Init(unsigned int width, unsigned int height, std::string name)
	{
		//Set parameters
		m_ScreenHeight = height;
		m_ScreenWidth = width;
		m_WindowName = name;
		//Create SDL Window
		m_Window = SDL_CreateWindow(name.c_str(), 0, 0, width, height, SDL_WINDOW_SHOWN);
		if(m_Window==NULL)
		{
			//Failed to create
			ErrorBox(_T("Failed to Create Window!"), _T("Window"));
			return ResultState::Fail;
		}
		//Set window surface
		m_ScreenSurface = SDL_GetWindowSurface(m_Window);
		m_WindowState = EngineState::Ok;
		
		return ResultState::Success;
	}
	ResultState Window::Init()
	{
		//Create SDL Window
		m_Window = SDL_CreateWindow(m_WindowName.c_str(), 0, 0, m_ScreenWidth, m_ScreenHeight, SDL_WINDOW_SHOWN);
		if (m_Window == NULL)
		{
			//Failed to create
			ErrorBox(_T("Failed to Create Window!"), _T("Window"));
			return ResultState::Fail;
		}
		//Set window surface
		m_ScreenSurface = SDL_GetWindowSurface(m_Window);
		m_WindowState = EngineState::Ok;

		return ResultState::Success;
	}
	ResultState Window::Shutdown()
	{
		//Deallocate surface
		if (m_ScreenSurface) 
		{
			SDL_FreeSurface(m_ScreenSurface);
			m_ScreenSurface = nullptr;
		}
		//Destroy window
		if (m_Window)
		{
			SDL_DestroyWindow(m_Window);
			m_Window = nullptr;
		}
		m_WindowState = EngineState::Shutdown;
		return ResultState::Success;
	}


	ResultState Window::SetScreenSize(unsigned int width, unsigned int height)
	{
		if (m_WindowState != EngineState::Ok)
		{
			m_ScreenHeight = height;
			m_ScreenWidth = width;
			return ResultState::Success;
		}
		else return ResultState::Fail;
	}

	ResultState Window::SetScreenName(std::string name)
	{
		if (m_WindowState != EngineState::Ok)
		{
			m_WindowName = name;
			return ResultState::Success;
		}
		else return ResultState::Fail;
	}

	SDL_Surface* Window::GetSurface()
	{
		return m_ScreenSurface;
	}
	SDL_Window* Window::GetWindow()
	{
		return m_Window;
	}


	ResultState Window::SetScreenPosition(unsigned int x, unsigned int y)
	{
		if(m_Window && m_WindowState==EngineState::Ok)
		SDL_SetWindowPosition(m_Window, x, y);
		else return ResultState::Fail;
		return ResultState::Success;
	}

	ResultState Window::ResizeWindow(unsigned int width, unsigned int height) //Resize already created window
	{
		if (m_WindowState == EngineState::Ok)
		{
			SDL_SetWindowSize(m_Window, width, height);
			m_ScreenWidth = width;
			m_ScreenHeight = height;
			return ResultState::Success;
		}
		else return ResultState::Fail;
	}


	unsigned int Window::GetScreenWidth()
	{
		return m_ScreenWidth;
	}
	unsigned int Window::GetScreenHeight()
	{
		return m_ScreenHeight;
	}
}