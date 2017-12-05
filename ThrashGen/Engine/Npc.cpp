#include "Npc.hpp"
namespace ThrashEngine {
	NPC::NPC()
	{
		m_virtualState = VirtualStateNPC;
		target = nullptr;
		properties.state = Idle;
		enableAI = true;
		timelastattack = 0;
		timeJump = 0;
	}
	NPC::~NPC()
	{
	}
	ResultState NPC::Update()
	{
		if (enableAI)
		{
			if (!target) //find target
			{

				std::vector<Sprite*>* ptr = m_managerPtr->GetSpritePtr();
				for (auto i = ptr->begin(); i != ptr->end(); i++)
				{
					//Chase and attack 
					if (*i != this &&  //Not the same obj
						((Object*)(*i))->GetVirtualState() != ThrashEngine::VirtualStateObject && //Is NPC
						((NPC*)(*i))->properties.fraction != properties.fraction) //Different fractions
					{
						if (ThrashEngine::DistanceSq(this, *i) < properties.range*properties.range)
						{
							target = (NPC*)(*i);
						}
					}
				}
			}
			if (target)
			{
				if (ThrashEngine::DistanceSq(this, target) > properties.range*properties.range)
				{
					target = nullptr;//Not in range
				}
				else if (ThrashEngine::DistanceSq(this, target) > properties.range*properties.InteractionRange) //Not in interaction range
				{
					properties.state = Moving;
					Vector vel = target->GetPos() - this->GetPos();
					vel.SetLen(properties.Acceleration);
					AddVelocity(vel);
					if (vel.LenSq() > properties.MaxSpeed*properties.MaxSpeed) vel.SetLen(properties.MaxSpeed);
				}
				else //target in interaction range
				{
					//atack target
					if (timelastattack > properties.interactionColdDown)
					{
						timelastattack = 0;
						double damage = properties.damage - target->properties.armor;
						if (damage < 0)damage = 0;
						target->properties.hp -= damage;
					}
				}
			}
			else
			{
				m_vel -= m_vel*properties.breakSpeed;
				if (m_vel.LenSq() < 1) m_vel = Vector(0, 0);
			}
		}
		timelastattack++;
		timeJump++;
		AnimationObject::Update();
		return ResultState::Success;
	}
	ResultState NPC::Draw(Graphics* graphics, double offx, double offy)
	{
		AnimationObject::Draw(graphics, offx, offy);

		//Health bar
		if (properties.maxhp) {
			graphics->SetColor(255, 0, 0, 255);
			graphics->DrawRect(m_x + offx, m_y - 10 + offy, m_width + 1, 10);
			graphics->SetColor(0, 255, 0, 255);
			graphics->DrawRect(m_x + offx, m_y - 10 + offy, m_width*((properties.hp + 1) / properties.maxhp), 10);
		}
		return ResultState::Success;
	}
	ResultState NPC::Update(Object* object, int event)
	{
		if (m_virtualState == VirtualStatePlayer)
		{
			if (*(double*)GetProperty("TimeBetweenJump").data < timeJump)
			{
				canJump = true;
				SetProperty("CanJump", true);
				timeJump = 0;
			}
		}
		if (object->GetVirtualState() == VirtualStateNPC)
		{

		}
		return ResultState::Success;
	}
	void NPC::EnableAI(bool flag)
	{
		enableAI = flag;
	}


	NPCProperty NPC::GetProperty(std::string propName)
	{
		auto it = m_property.find(propName);
		if (it != m_property.end()) return it->second; //Texture was found
		return NPCProperty();
	}
	NPCProperty NPC::SetProperty(std::string propName, NPCProperty property)
	{
		auto it = m_property.find(propName);
		if (it != m_property.end())
		{
			it->second.type = property.type;
			delete it->second.data;
			it->second.data = property.data;
			return it->second;
		}
		m_property.insert({ propName,property });
		return property;
	}

	NPCProperty NPC::SetProperty(std::string propName, double value)
	{
		auto it = m_property.find(propName);
		NPCProperty prop;
		prop.type = DOUBLE;
		double* ptr = new double;
		*ptr = value;
		prop.data = ptr;
		if (it != m_property.end())
		{
			it->second.type = prop.type;
			delete it->second.data;
			it->second.data = prop.data;
			return it->second;
		}
		m_property.insert({ propName,prop });
		return prop;
	}
	NPCProperty NPC::SetProperty(std::string propName, std::string value)
	{
		auto it = m_property.find(propName);
		NPCProperty prop;
		prop.type = DOUBLE;
		std::string* ptr = new std::string;
		*ptr = value;
		prop.data = ptr;
		if (it != m_property.end())
		{
			it->second.type = prop.type;
			delete it->second.data;
			it->second.data = prop.data;
			return it->second;
		}
		m_property.insert({ propName,prop });
		return prop;
	}
	NPCProperty NPC::SetProperty(std::string propName, char value)
	{
		auto it = m_property.find(propName);
		NPCProperty prop;
		prop.type = DOUBLE;
		char* ptr = new char;
		*ptr = value;
		prop.data = ptr;
		if (it != m_property.end())
		{
			it->second.type = prop.type;
			delete it->second.data;
			it->second.data = prop.data;
			return it->second;
		}
		m_property.insert({ propName,prop });
		return prop;
	}
	NPCProperty NPC::SetProperty(std::string propName, bool value)
	{
		auto it = m_property.find(propName);
		NPCProperty prop;
		prop.type = DOUBLE;
		bool* ptr = new bool;
		*ptr = value;
		prop.data = ptr;
		if (it != m_property.end())
		{
			it->second.type = prop.type;
			delete it->second.data;
			it->second.data = prop.data;
			return it->second;
		}
		m_property.insert({ propName,prop });
		return prop;
	}

}