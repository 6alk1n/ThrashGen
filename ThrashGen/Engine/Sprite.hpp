#pragma once
#include "Graphics.hpp"
/***********************
Sprite.hpp
Sprite class - a basic object that contains it's position, texture, uv coordinates(basic stuff for drawing)
************************/
namespace ThrashEngine {
	class Sprite
	{
	public:
		Sprite();
		virtual ~Sprite();
		SDL_Texture* GetTexture();
		void SetTexture(SDL_Texture*);
		virtual ResultState Draw(Graphics*, double offx=0,double offy=0);

		virtual ResultState Update(Sprite*); 
		virtual ResultState Update();

		void SetPos(double x, double y);
		void SetPos(Vector pos);
		void SetUV(int u, int v, int uend, int vend);
		void Move(double x, double y);
		void Move(Vector mov);
		double GetX();
		double GetY();
		Vector GetPos();
		void GetUV(int&, int&,int&,int&);
		double GetWidth();
		double GetHeight();
		void SetSize(double, double);
		Rectangle GetRect();
		int GetID();
		void SetID( int);
	protected:
		SDL_Texture* m_texture;
		double m_x, m_y;
		int m_u, m_v,m_uend,m_vend;
		double m_width, m_height;
		bool m_killSprite;
		friend class ObjectManager;
		int m_SpriteID;
	};
}