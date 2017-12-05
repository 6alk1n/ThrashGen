#include "Sprite.hpp"
namespace ThrashEngine {
	Sprite::Sprite()
	{
		m_texture = nullptr;
		m_x = m_y = m_u = m_v = m_uend = m_vend = 0;
		m_killSprite = true;
	}
	Sprite::~Sprite()
	{

	}
	SDL_Texture* Sprite::GetTexture()
	{
		return m_texture;
	}
	void Sprite::SetTexture(SDL_Texture* texture)
	{
		m_texture = texture;
		SDL_QueryTexture(m_texture, NULL, NULL, &m_uend, &m_vend);
	}
	ResultState Sprite::Draw(Graphics* graphics, double offx, double offy)
	{
		SDL_Rect dest;
		dest.x = (int)m_x+ (int)offx;
		dest.y = (int)m_y+ (int)offy;
		dest.w = (int)m_width;
		dest.h = (int)m_height;
		SDL_Rect src;
		src.x = m_u;
		src.y = m_v;
		src.w = m_uend;
		src.h = m_vend;
		return graphics->DrawTexture(m_texture, &dest, &src);
	}
	void  Sprite::SetPos(double x, double y)
	{
		m_x = x; m_y = y;
	}
	void Sprite::SetPos(Vector pos)
	{
		m_x = pos.x;
		m_y = pos.y;
	}
	void  Sprite::SetUV(int u, int v, int uend, int vend)
	{
		m_u = u; m_v = v; m_uend = uend; m_vend = vend;
	}
	void  Sprite::Move(double x, double y)
	{
		m_x += x;
		m_y += y;
	}
	void Sprite::Move(Vector mov)
	{
		m_x += mov.x;
		m_y += mov.y;
	}
	double  Sprite::GetX()
	{
		return m_x;
	}
	double  Sprite::GetY()
	{
		return m_y;
	}
	void  Sprite::GetUV(int& u, int& v, int& uend, int& vend)
	{
		u = m_u;
		v = m_v;
		uend = m_uend;
		vend = m_vend;
	}
	Vector Sprite::GetPos()
	{
		return Vector(m_x, m_y);
	}
	double Sprite::GetWidth()
	{
		return m_width;
	}
	double Sprite::GetHeight()
	{
		return m_height;
	}
	void Sprite::SetSize(double w , double h)
	{
		m_width = w;
		m_height = h;
	}

	ResultState Sprite::Update(Sprite* spr)
	{
		return ResultState::Success;
	}
	ResultState Sprite::Update()
	{
		return ResultState::Success;
	}
	Rectangle Sprite::GetRect()
	{
		return Rectangle(m_x, m_y, m_width, m_height);
	}
	int Sprite::GetID()
	{
		return m_SpriteID;
	}
	void Sprite::SetID( int id)
	{
		m_SpriteID = id;
	}
}