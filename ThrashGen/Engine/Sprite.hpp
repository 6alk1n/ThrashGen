#pragma once
#include "Graphics.hpp"
/***********************
Sprite.hpp
Sprite class - a basic object that contains it's position, texture, uv coordinates(basic stuff for drawing)
************************/


//!!!NEW SYSTEM!!!

namespace ThrashEngine {

	const int VirtualLevelSprite = 0;

  class Sprite
  {
  public:
    //Methods
    Sprite();
	virtual ~Sprite();
    virtual ResultState	Draw(Graphics*, double offx=0,double offy=0);
	virtual ResultState Update(Sprite*,int flags=0);
	virtual ResultState Update(double timestep=0);

	void Move(double x,double y);
	void Move(Vector vec);
	void Move(VectorFull vec); 
	void Move(Rectangle rect);

	//Setters
	void SetTexture(SDL_Texture* texture);
	void SetSize(double, double);

	//Getters
	Rectangle GetRect();
	Vector GetPos();
	void GetUV(int& u, int& v, int& uend, int& vend);

	//Members
	SDL_Texture* m_texture;
	Rectangle m_pos;
	bool m_kill;
	Rectangle m_textureUV;
	unsigned int GetVirtualState();
  protected:
	unsigned int __virtualization_level;
	//unsigned int __unused4byte;

  };

  static double DistanceSq(Sprite* sprite1, Sprite* sprite2)
  {
	  return (sprite1->m_pos.GetVector() - sprite2->m_pos.GetVector()).LenSq();
  }
}



/*

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
*/