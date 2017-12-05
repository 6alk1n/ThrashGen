#include "Sprite.hpp"
namespace ThrashEngine {
	Sprite::Sprite()
	{
		m_texture = nullptr;

		m_pos = m_textureUV=0;
		m_kill = true;
		__virtualization_level=VirtualLevelSprite;
	}
	Sprite::~Sprite()
	{

	}
	void Sprite::SetTexture(SDL_Texture* texture)
	{
		m_texture = texture;
		int u, v;
		u = v = 0;
		SDL_QueryTexture(m_texture, NULL, NULL, &u,&v);
		m_textureUV.w = u;
		m_textureUV.h = v;
	}
	ResultState Sprite::Draw(Graphics* graphics, double offx, double offy)
	{
		SDL_Rect dest;
		dest.x = (int)m_pos.x+ (int)offx;
		dest.y = (int)m_pos.y+ (int)offy;
		dest.w = (int)m_pos.w;
		dest.h = (int)m_pos.h;
		SDL_Rect src;
		src.x = m_textureUV.x;
		src.y = m_textureUV.y;
		src.w = m_textureUV.w;
		src.h = m_textureUV.h;
		return graphics->DrawTexture(m_texture, &dest, &src);
	}
	ResultState Sprite::Update(Sprite* spr, int)
	{
		return ResultState::Success;
	}
	ResultState Sprite::Update(double)
	{
		return ResultState::Success;
	}
	void  Sprite::Move(double x, double y)
	{
		m_pos.x += x;
		m_pos.y += y;
	}
	void Sprite::Move(Vector mov)
	{
		m_pos += mov;
	}
	void Sprite::Move(VectorFull vec)
	{
		m_pos += Vector(vec.x,vec.y);
	}
	void Sprite::Move(Rectangle rect)
	{
		m_pos += rect;
	}	
	void Sprite::SetSize(double w, double h)
	{
		m_pos.w = w;
		m_pos.h = h;
	}

	Rectangle Sprite::GetRect()
	{
		return m_pos;
	}

	Vector Sprite::GetPos()
	{
		return Vector(m_pos.x, m_pos.y);
	}	
	void  Sprite::GetUV(int& u, int& v, int& uend, int& vend)
	{
		u = m_textureUV.x;
		v = m_textureUV.y;
		uend = m_textureUV.w;
		vend = m_textureUV.h;
	}

	unsigned int Sprite::GetVirtualState()
	{
		return __virtualization_level;
	}
}