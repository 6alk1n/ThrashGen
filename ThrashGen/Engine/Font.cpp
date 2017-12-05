#include "Font.hpp"
namespace ThrashEngine 
{
	Font::Font()
	{
		TTF_Init();
		m_text = nullptr;
		m_Font = nullptr;
	}
	Font::~Font()
	{

	}

	ResultState Font::LoadFont(std::string font,int size)
	{
		m_Font = TTF_OpenFont(font.c_str() , size);
		if (m_Font == NULL) return ResultState::Fail;
		return ResultState::Success;
	}

	SDL_Texture* Font::RenderTexture(Graphics* graphics,std::string text, SDL_Color color)
	{
		if (m_Font == nullptr) return nullptr;

		//Render text surface
		SDL_Surface* textSurface = TTF_RenderText_Solid(m_Font, text.c_str(), color);
		if (textSurface == NULL)
		{
		//	printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		}
		else
		{
			if (m_text)
			{
				//Free loaded images
				SDL_DestroyTexture(m_text);
			}
			//Create texture from surface pixels
			m_text = SDL_CreateTextureFromSurface(graphics->GetRenderer(), textSurface);
			if (m_text == NULL)
			{
				printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				//Get image dimensions
				m_width = textSurface->w;
				m_height = textSurface->h;
			}

			//Get rid of old surface
			SDL_FreeSurface(textSurface);
		}
		return m_text;
	}
	SDL_Texture* Font::GetRenderedTexture()
	{
		return m_text;
	}


	FontField::FontField()
	{
		m_font = nullptr;
		m_needsUpdate = false;
		m_pos = m_size=Vector(0,0);
	}
	FontField::~FontField()
	{
	}
	void FontField::SetFont(Font* font)
	{
		m_font = font;
	}

	void  FontField::SetGraphics(Graphics* graph)
	{
		m_graphicsPtr = graph;
	}
	void FontField::SetPos(Vector pos)
	{
		m_pos = pos;
	}
	void FontField::SetSize(Vector size)
	{
		m_size = size;
	}
	void FontField::ClearField()
	{
		m_text.clear();
		m_needsUpdate = true;
	}
	void FontField::AddField(std::string str)
	{
		m_text.append(str);
		m_needsUpdate = true;
	}
	FontField& FontField::operator<<(std::string str)
	{
		m_text.append(str);
		m_needsUpdate = true;
		return *this;
	}
	FontField& FontField::operator<<(double val)
	{
		m_text.append(DoubleToStr(val));
		m_needsUpdate = true;
		return *this;
	}
	void FontField::Print(int val)
	{
		m_text.append(IntToStr(val));
		m_needsUpdate = true;
	}
	SDL_Texture* FontField::GetRenderedTexture()
	{
		if (m_font == nullptr) return nullptr;
		return m_font->GetRenderedTexture();

	}
	void FontField::SetColor(SDL_Color color)
	{
		m_textColor = color;
	}
	ResultState FontField::Render()
	{
		if (m_needsUpdate)
		{
			m_font->RenderTexture(m_graphicsPtr, m_text, m_textColor);
			m_needsUpdate = false;
		}
		SDL_Rect r;
		r.x = (int)m_pos.x;
		r.y = (int)m_pos.y;
		r.w = (int)m_size.x;
		r.h = (int)m_size.y;
		m_graphicsPtr->DrawTexture(m_font->GetRenderedTexture(), &r);
		return ResultState::Success;
	}
}
