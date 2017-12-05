#include "Object.hpp"
#include <iostream>
namespace ThrashEngine
{
	Object::Object()
	{
		m_active = true;
		m_collideable = true;
		m_static = false;
		m_virtualState = VirtualStateObject;
		m_debugDraw = true;
	}

	Object::Object(Sprite* sprite) :Object()
	{
		m_texture = sprite->GetTexture();
		m_width = sprite->GetWidth();
		m_height = sprite->GetHeight();
		sprite->GetUV(m_u, m_v, m_uend, m_vend);
	}
	Object::~Object() {}
	ResultState Object::SetVel(double x, double y)
	{
		m_vel.x = x;
		m_vel.y = y;
		return ResultState::Success;
	}
	ResultState Object::SetVel(Vector v)
	{
		m_vel = v;
		return ResultState::Success;
	}
	Vector Object::GetVel()
	{
		return m_vel;
	}
	ResultState Object::Update()
	{
		if (m_active)
		{
			m_x += m_vel.x;
			m_y += m_vel.y;
			m_x += m_force.x;
			m_y += m_force.y;
			m_force.x = m_force.y = 0;
		}
		return ResultState::Success;
	}
	ResultState Object::Update(Object*,int)
	{
		return ResultState::Success;
	}

	bool Object::IsActive()
	{
		return m_active;
	}
	bool Object::IsCollideable()
	{
		return m_collideable;
	}
	ResultState  Object::Force(double x, double y)
	{
		m_force.x += x;
		m_force.y += y;
		return ResultState::Success;
	}
	ResultState  Object::Force(Vector v)
	{
		m_force += v;
		return ResultState::Success;
	}
	void Object::AddVelocity(double x, double y)
	{
		m_vel.x += x;
		m_vel.y += y;
	}
	void Object::AddVelocity(Vector v)
	{
		m_vel += v;
	}
	void Object::SetVelX(double x)
	{
		m_vel.x = x;
	}
	void Object::SetVelY(double y)
	{
		m_vel.y = y;
	}
	Vector Object::GetForce()
	{
		return m_force;
	}
	ResultState Object::SetForce(double x, double y)
	{
		m_force.x = x;
		m_force.y = y;
		return ResultState::Success;
	}
	ResultState Object::SetForce(Vector v)
	{
		m_force = v;
		return ResultState::Success;
	}

	ResultState Object::SetForceX(double x)
	{
		m_force.x = x;
		return ResultState::Success;
	}
	ResultState Object::SetForceY(double y)
	{
		m_force.y = y;
		return ResultState::Success;
	}
	void Object::SetCollision(bool flag)
	{
		m_collideable = flag;
	}
	void Object::SetActive(bool flag)
	{
		m_active = flag;
	}

	ResultState Object::Draw(Graphics* graphics, double offx, double offy)
	{
		if (m_active) {
			Sprite::Draw(graphics, offx, offy);
			if (m_debugDraw) {
				if (m_collideable)
				{
					graphics->SetColor(0, 255, 0, 0);
					graphics->DrawRectOut(m_x + offx, m_y + offy, m_width, m_height);
				}
				else
				{
					graphics->SetColor(0, 0, 0, 0);
					graphics->DrawRectOut(m_x + offx, m_y + offy, m_width, m_height);
				}
			}
		}
		return ResultState::Success;
	}
	int Object::GetVirtualState()
	{
		return m_virtualState;
	}

	void Object::SetVirtualState(int v)
	{
		m_virtualState = v;
	}
	void Object::SetDebugDraw(bool flag)
	{
		m_debugDraw = flag;
	}
	void Object::SetName(std::string str)
	{
		m_name = str;
	}
	std::string Object::GetName()
	{
		return m_name;
	}
}