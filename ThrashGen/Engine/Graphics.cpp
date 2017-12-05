#include "Graphics.hpp"
#include "Application.hpp"
namespace ThrashEngine
{
	Graphics::Graphics()
	{
		m_renderer = nullptr;
		m_SystemName = "graphics";
		m_state = EngineState::Invalid;

//	SystemListPtr->push_back((System*)this);
	}
	Graphics::~Graphics()
	{
		if (m_renderer) SDL_DestroyRenderer(m_renderer);
	}
	ResultState Graphics::Init(SDL_Window* window)
	{

		int vsync = SDL_GL_SetSwapInterval(0);
		//vsync = 0;
		if (vsync == 0)
		{
			std::cout << "Vsync is not supported! Using in-game frame limiter" << std::endl;
			m_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		}
		else {
			m_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		}
		if (m_renderer == NULL)
		{
			ErrorBox(_T("Graphics error"), _T("Failed to create renderer SDL"));
			m_state = EngineState::Failed;
			return ResultState::Fail;
		}
		else
		{
			//Initialize renderer color
			SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0xFF);
			m_state = EngineState::Ok;
			//Create default viewport
			SDL_Rect rect;
			rect.x = 0;
			rect.y = 0;
			SDL_GetWindowSize(window, &rect.w, &rect.h); //Get window size from window ptr
			if (!(CreateViewPort("default", rect) && SetViewPort("default"))) return ResultState::Fail;
			m_pixformat = SDL_GetWindowSurface(window)->format;
		}
		
		return ResultState::Success;
	}
	SDL_Renderer* Graphics::GetRenderer()
	{
		return m_renderer;
	}
	SDL_Texture* Graphics::CreateTexture(SDL_Surface* surface)
	{
		return SDL_CreateTextureFromSurface(m_renderer, surface);
	}
	SDL_Texture* Graphics::CreateTexture(SDL_Surface* surface, Uint32 color)
	{
		SDL_SetColorKey(surface, SDL_TRUE, color);
		return CreateTexture(surface);
	}

	ResultState Graphics::SetColor(int r, int g, int b, int a)
	{
		if (SDL_SetRenderDrawColor(m_renderer, r, g, b, a) == 0) return ResultState::Success;
		else return ResultState::Fail;

	}
	ResultState Graphics::SetColor(Uint32 color)
	{
		if (SDL_SetRenderDrawColor(m_renderer, color && 255, (color << 8) && 255, (color << 16) && 255, 255) == 0) return ResultState::Success;
		else return ResultState::Fail;
	}
	ResultState Graphics::SetColor(SDL_Color color)
	{
		if (SDL_SetRenderDrawColor(m_renderer, color.r,color.g,color.b,color.a) == 0) return ResultState::Success;
		else return ResultState::Fail;
	}

	ResultState Graphics::DrawTexture(SDL_Texture* texture)
	{
		//Render texture to screen
		if (texture == nullptr) return ResultState::Fail;
		if (SDL_RenderCopy(m_renderer, texture, NULL, NULL) == 0) return ResultState::Success;
		else return ResultState::Fail;
	}
	ResultState Graphics::DrawTexture(SDL_Texture* texture, SDL_Rect* dest)
	{
		//Render texture to screen
		if (texture == nullptr || dest == nullptr) return ResultState::Fail;
		if (SDL_RenderCopy(m_renderer, texture, NULL, dest) == 0) return ResultState::Success;
		else return ResultState::Fail;
	}
	ResultState Graphics::DrawTexture(SDL_Texture* texture, SDL_Rect* dest, SDL_Rect* src)
	{
		//Render texture to screen
		if (texture == nullptr || dest == nullptr || src == nullptr) return ResultState::Fail;
		if (SDL_RenderCopy(m_renderer, texture, src, dest) == 0) return ResultState::Success;
		else return ResultState::Fail;
	}
	ResultState Graphics::CreateViewPort(std::string name,SDL_Rect rect) //Create new viewport, returns false if viewport names intersect
	{
		ViewPort* viewportcheck = GetViewPort(name);
		if (viewportcheck != nullptr) return ResultState::Fail;
		ViewPort viewport;
		viewport.m_name = name;
		viewport.m_view = rect;
		m_viewport.push_back(viewport);
		return ResultState::Success;
	}
	ViewPort* Graphics::GetViewPort(std::string name)	//Getter for viewport
	{
		for (auto i = m_viewport.begin(); i != m_viewport.end(); i++)
		{
			if (i->m_name == name) return &(*i);
		}
		return nullptr;
	}
	ResultState Graphics::SetViewPort(std::string name)	//Set viewport
	{
		ViewPort* viewport = GetViewPort(name);
		if (viewport != nullptr)
		{
			SDL_RenderSetViewport(m_renderer, &viewport->m_view);
			return ResultState::Success;
		}
		return ResultState::Fail;
	}

	ResultState Graphics::DrawPixel(double x, double y, Uint32 color) //Draw pixel on scree
	{
		SDL_SetRenderDrawColor(m_renderer, color && 255, (color << 8) && 255, (color << 16) && 255, 255);
		return DrawPixel(x, y);
	}
	ResultState Graphics::DrawPixel(double x, double y)
	{
		if (SDL_RenderDrawPoint(m_renderer, (int)x, (int)y) == 0) return ResultState::Success;
		else return ResultState::Fail;
	}
	ResultState Graphics::DrawRectXY(SDL_Rect rect)
	{
		if (SDL_RenderFillRect(m_renderer, &rect) == 0) return ResultState::Success;
		else return ResultState::Fail;
	}
	ResultState Graphics::DrawRectXY(double x, double y, double w, double h)
	{
		SDL_Rect rect;
		rect.x = (int)x;
		rect.y = (int)y;
		rect.w = (int)(w - x);
		rect.h = (int)(h - y);
		return DrawRectXY(rect);
	}
	ResultState Graphics::DrawRect(SDL_Rect rect)//Draw rectangle on screen
	{
		rect.w += rect.x;
		rect.h += rect.y;
		if (SDL_RenderFillRect(m_renderer, &rect) == 0) return ResultState::Success;
		else return ResultState::Fail;
	}
	ResultState Graphics::DrawRect(double x, double y, double w, double h)//Draw rectangle on screen with coords
	{
		SDL_Rect rect;
		rect.x = (int)x;
		rect.y = (int)y;
		rect.w = (int)w;
		rect.h = (int)h;
		if (SDL_RenderFillRect(m_renderer, &rect) == 0) return ResultState::Success;
		else return ResultState::Fail;
	}
	ResultState Graphics::DrawLine(double x1, double y1, double x2, double y2) //Draw line on screen
	{
		if (SDL_RenderDrawLine(m_renderer,(int)x1, (int)y1, (int)x2, (int)y2) == 0) return ResultState::Success;
		else return ResultState::Fail;
	}
	ResultState Graphics::DrawLine(SDL_Rect rect) //Draw line on screen
	{
		return DrawLine((double)rect.x, (double)rect.y, (double)rect.w, (double)rect.h);
	}
	ResultState Graphics::DrawRectOutXY(SDL_Rect rect)//Draw rectangle borders on screen
	{
		return DrawRectOutXY((double)rect.x, (double)rect.y, (double)rect.w, (double)rect.h);
	}
	ResultState Graphics::DrawRectOutXY(double x, double y, double w, double h)//Draw rectangle borders on screen
	{
		if ((SDL_RenderDrawLine(m_renderer, (int)x, (int)y, (int)w, (int)y) == 0) &&
			(SDL_RenderDrawLine(m_renderer, (int)w, (int)y, (int)w, (int)h) == 0) &&
			(SDL_RenderDrawLine(m_renderer, (int)w, (int)h, (int)x, (int)h) == 0) &&
			(SDL_RenderDrawLine(m_renderer, (int)x, (int)h, (int)x, (int)y) == 0))return ResultState::Success;
		else return ResultState::Fail;
	}
	ResultState Graphics::DrawRectOut(SDL_Rect rect)//Draw rectangle borders on screen
	{
		return DrawRectOutXY((float)rect.x, (float)rect.y, (float)(rect.w+rect.x), (float)(rect.h+rect.y));
	}
	ResultState Graphics::DrawRectOut(double x, double y, double w, double h)//Draw rectangle borders on screen
	{
		if ((SDL_RenderDrawLine(m_renderer, (int)x, (int)y, (int)(w+x), (int)y) == 0) &&
			(SDL_RenderDrawLine(m_renderer, (int)(w+x), (int)y, (int)(w+x), (int)(h+y)) == 0) &&
			(SDL_RenderDrawLine(m_renderer, (int)(w+x), (int)(h+y), (int)x, (int)(h+y)) == 0) &&
			(SDL_RenderDrawLine(m_renderer, (int)x, (int)(h+y), (int)x, (int)y) == 0))return ResultState::Success;
		else return ResultState::Fail;
	}

	ResultState Graphics::SetVsync(bool flag)
	{
		if(flag)
			SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
		else
			SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0");
		
		return ResultState::Success;
	}

	SDL_PixelFormat* Graphics::GetPixelFormat()
	{
		return m_pixformat;
	}

	Uint32 Graphics::GetColor(Uint8 r , Uint8 g, Uint8 b)
	{
		return SDL_MapRGB(m_pixformat, r, g, b);
	}

	ResultState Graphics::SetRendererScale(float w, float h)
	{
		if (SDL_RenderSetScale(m_renderer, w, h)==0)
		return ResultState::Success;
		else return ResultState::Fail;
	}

	ResultState Graphics::GetRendererScale(float& w, float& h)
	{
		SDL_RenderGetScale(m_renderer, &w, &h);
		return ResultState::Success;
	}

	EngineState Graphics::Restart(std::list<PropertyClass*> list)
	{

		for (auto i = list.begin(); i != list.end(); i++)
		{		
			// (*(*i)->name == "width")
			//{
			//	screen->m_window->ResizeWindow(*(double*)(w->data), *(double*)(h->data));
			//}
		}

		/*
		ThrashEngine::NPCProperty* w = screen->AppParams.GetProperty("width");
		ThrashEngine::NPCProperty* h = screen->AppParams.GetProperty("height");
		ThrashEngine::NPCProperty* vsync = screen->AppParams.GetProperty("vsync");
		screen->m_window->ResizeWindow(*(double*)(w->data), *(double*)(h->data));
		screen->m_window->SetVsync(*(bool*)(vsync->data));
		screen->m_graphics->SetVsync(*(bool*)(vsync->data));*/
		return EngineState::Ok;
	}
}