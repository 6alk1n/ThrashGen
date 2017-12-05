#pragma once
#include "Core.hpp"
#include <vector>
/*
Class is used for graphics rendering. 
Contains Renderer of window. Also used for drawing and creating textures
*/
namespace ThrashEngine {

	class ViewPort
	{
	public:
		std::string m_name;
		SDL_Rect m_view;
	};
	class Graphics
	{
	public:
		Graphics();
		~Graphics();
		ResultState Init(SDL_Window*); //Creates renderer 
		SDL_Renderer* GetRenderer();   
		SDL_Texture* CreateTexture(SDL_Surface*); //Creates a texture from surface and returns it (surface is not deallocated after creating a texture!)
		SDL_Texture* CreateTexture(SDL_Surface*,Uint32); //Creates a texture from surface with colorkey and returns it (surface is not deallocated after creating a texture!)

		ResultState SetColor(int r, int g, int b, int a);// Set renderer color
		ResultState SetColor(Uint32);// Set renderer color

		ResultState DrawTexture(SDL_Texture*); //Draw texture on whole screen
		ResultState DrawTexture(SDL_Texture*, SDL_Rect*); //Draw texture in the specific point
		ResultState DrawTexture(SDL_Texture*,SDL_Rect*,SDL_Rect*); //Draw the specific part of texture in the specific point

		ResultState CreateViewPort(std::string,SDL_Rect); //Create new viewport, returns false if viewport names intersect
		ViewPort* GetViewPort(std::string);	//Getter for viewport
		ResultState SetViewPort(std::string);	//Set viewport

		//Geometry drawing
		ResultState DrawPixel(double x, double y, Uint32); //Draw pixel on screen with color
		ResultState DrawPixel(double x, double y); //Draw pixel on screen
		ResultState DrawRectXY(SDL_Rect);//Draw rectangle on screen
		ResultState DrawRectXY(double x, double y, double w, double h);//Draw rectangle on screen with coords
		ResultState DrawRect(SDL_Rect);//Draw rectangle on screen
		ResultState DrawRect(double x, double y, double w, double h);//Draw rectangle on screen with coords
		ResultState DrawLine(double x1, double y1, double x2, double y2); //Draw line on screen
		ResultState DrawLine(SDL_Rect); //Draw line on screen
		ResultState DrawRectOutXY(SDL_Rect);//Draw rectangle borders on screen
		ResultState DrawRectOutXY(double x, double y, double w, double h);//Draw rectangle borders on screen
		ResultState DrawRectOut(SDL_Rect);//Draw rectangle borders on screen
		ResultState DrawRectOut(double x, double y, double w, double h);//Draw rectangle borders on screen

		ResultState SetRendererScale(float,float);
		ResultState GetRendererScale(float&, float&);
		
		SDL_PixelFormat* GetPixelFormat();
		Uint32 GetColor(Uint8, Uint8, Uint8);
	protected:
		SDL_Renderer* m_renderer;
		SDL_PixelFormat* m_pixformat;
		EngineState m_state;

		std::vector<ViewPort> m_viewport;
		std::string m_currentport;
	};
}