#include "Application.hpp"

namespace ThrashEngine
{
	Application::Application()
	{
		m_window = nullptr;
		m_input = nullptr;
		m_graphics = nullptr;
		m_state = EngineState::Invalid;
		m_done = false;
		m_fps = 60;
	}
	Application::~Application()
	{

	}
	ResultState Application::Init()
	{
		if (m_window->Init()!=ResultState::Success)
		{
			m_state = EngineState::Failed;
			return ResultState::Fail;
		}
		if (m_graphics->Init(m_window->GetWindow()) != ResultState::Success)
		{
			m_state = EngineState::Failed;
			return ResultState::Fail;
		}
		if (m_audio->Init() != ResultState::Success)
		{
			m_state = EngineState::Failed;
			return ResultState::Fail;
		}
		m_state = EngineState::Ok;
		return ResultState::Success;
	}
	ResultState Application::Run()
	{
		//Event handler
		SDL_Event e;
		OnInit();

		while (!m_done)
		{
			m_monitor.StartMonitor("Toogle");
			//Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					m_done = true;
				}
				//User presses a key
				else if (e.type == SDL_KEYDOWN)
				{
					m_input->Press(e.key.keysym.sym);
				}
				else if (e.type == SDL_KEYUP)
				{
					m_input->Release(e.key.keysym.sym);
				}
				else if (e.type == SDL_MOUSEMOTION)
				{
					m_input->SetMousePos(e.button.x, e.button.y);
					//m_input->SetDelta(e.motion, e.motion.yrel);
				}
				else if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					m_input->Press(e.button.button + 255);
					
				}
				else if (e.type == SDL_MOUSEBUTTONUP)
				{

					m_input->Release(e.button.button +255);
				}
			}
			//Clear screen
			SDL_SetRenderDrawColor(m_graphics->GetRenderer(), 0, 0, 0, 0xFF); 
			SDL_RenderClear(m_graphics->GetRenderer());

			m_monitor.StartMonitor("DrawingFrame");
			Draw();
			m_monitor.EndMonitor("DrawingFrame");

			m_monitor.StartMonitor("UpdatingFrame");
			Update();	
			m_monitor.EndMonitor("UpdatingFrame");

			m_input->Update();


			//Update screen

			SDL_RenderPresent(m_graphics->GetRenderer());

			m_monitor.EndMonitor("Toogle");

			int total = m_monitor.GetMonitor("Toogle").diffTime;
			total -= m_monitor.GetMonitor("DrawingFrame").diffTime;
			total -= m_monitor.GetMonitor("UpdatingFrame").diffTime;
			
			if (m_monitor.GetMonitor("Toogle").diffTime < 1000 / m_fps)
			{
		//		SDL_Delay((1000/m_fps)- m_monitor.GetMonitor("Toogle").diffTime);
			}


		}
		OnShutdown();
		return ResultState::Success;
	}
	ResultState Application::Shutdown()
	{
		if (m_window->Shutdown() != ResultState::Success)
		{
			m_state = EngineState::Failed;
			return ResultState::Fail;
		}
		m_state = EngineState::Ok;
		return ResultState::Success;
	}
	ResultState Application::Create()
	{
		//Create new Window
		m_window = new Window();
		m_input = new Input();
		m_graphics = new Graphics();
		m_state = EngineState::Created;
		m_audio = new AudioMaster();
		return ResultState::Success;
	}

	ResultState Application::Draw() { return ResultState::Success; }
	ResultState Application::Update() { return ResultState::Success; }

	Window* Application::GetWindow()
	{
		return m_window;
	}

	ResultState Application::OnInit()
	{
		return ResultState::Success;
	}
	ResultState Application::OnShutdown()
	{
		return ResultState::Success;
	}
}