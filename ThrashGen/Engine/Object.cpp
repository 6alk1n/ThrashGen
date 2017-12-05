#include "Object.hpp"
#include <iostream>
namespace ThrashEngine
{
	Object::Object()
	{
		m_active = true;
		m_collideable = true;
		m_static = false;
		__virtualization_level = VirtualLevelObject;
		m_debug = true; 
		m_property = new PropertyClass;
	}

	Object::Object(Sprite* sprite) :Sprite()
	{
		m_texture = sprite->m_texture;
		m_pos.w = sprite->m_pos.w;
		m_pos.h = sprite->m_pos.h;
		m_textureUV = sprite->m_textureUV;
		__virtualization_level = VirtualLevelObject;
		m_property = new PropertyClass;
	}
	Object::~Object(){}

	ResultState Object::Update(double timestep)
	{
		if (m_active)
		{
			m_pos.x += m_vel.x;
			m_pos.y += m_vel.y;
		}
		return ResultState::Success;
	}

	ResultState Object::Update(Object*,int)
	{
		return ResultState::Success;
	}

	ResultState Object::Draw(Graphics* graphics, double offx, double offy)
	{
		if (m_active) {
			Sprite::Draw(graphics, offx, offy);
			if (m_debug) {
				if (m_collideable)
				{
					graphics->SetColor(0, 255, 0, 0);
					graphics->DrawRectOut(m_pos.x + offx, m_pos.y + offy, m_pos.w, m_pos.h);
				}
				else
				{
					graphics->SetColor(0, 0, 0, 0);
					graphics->DrawRectOut(m_pos.x + offx, m_pos.y + offy, m_pos.w, m_pos.h);
				}
			}
		}
		return ResultState::Success;
	}
	unsigned int Object::GetVirtualizationLevel()
	{
		return __virtualization_level;
	}
}