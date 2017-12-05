#pragma once
/***********
//Font.hpp has font class for font rendering. FontField for easier manipulation with text.
Uses SDL2.0 ttf stuff;
************/
#include "Core.hpp"
#include <SDL_ttf.h>
#include <string>
#include <list>
#include "Graphics.hpp"
namespace ThrashEngine {
	class Font
	{
	public:
		Font();
		~Font();

		ResultState LoadFont(std::string,int); //Load font (filepath,size)

		SDL_Texture* RenderTexture(Graphics*,std::string,SDL_Color);//Create Texture (graphicsPtr,text,textColor)
		SDL_Texture* GetRenderedTexture();//Get already rendered texture
	
	protected:
		TTF_Font* m_Font; //ptr on font
		SDL_Texture* m_text; //rendered texture(text)
		int m_width, m_height; //size of rendered texture
	};
	class FontField
	{
	public:
		FontField();
		~FontField();
		void SetFont(Font*);	//Set fontPtr for field
		void SetGraphics(Graphics*);	//Set graphicsPtr
		void SetPos(Vector);	//Set Position of field
		void SetSize(Vector);	//Size of field
		virtual void ClearField();		//Clear text from field
		void AddField(std::string);	//Add text to field
		FontField& operator<<(std::string);	//operator add text to field
		FontField& operator<<(double);//operator add double to field
		void Print(int);
		SDL_Texture* GetRenderedTexture();//Get rendered text
		void SetColor(SDL_Color);//Set FieldColor
		virtual ResultState Render();//Draw field
	protected:
		Font* m_font;//ptr to font
		Graphics* m_graphicsPtr;//ptr to graphics
		Vector m_pos;
		Vector m_size;
		std::string m_text; //string for field
		bool m_needsUpdate; //used int render(creates text only once withous changes)
		SDL_Color m_textColor;
	};
	class Text :public FontField
	{
	public:
		Text();
		~Text();
		void SetLetterSize(unsigned int,unsigned int);
		void EndLine(); //Start New Line
		virtual ResultState Render();//Draw field
		virtual void ClearField();		//Clear text from field
		void SetDrawStyle(unsigned int);
		void SetSize(Vector);
	protected:
		unsigned int m_lettersizewidth;
		unsigned int m_lettersizeheight;
		std::list<std::string> m_output_text;
		unsigned int m_drawstyle;
		Vector m_size;
	};
}