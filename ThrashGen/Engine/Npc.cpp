#include "Npc.hpp"
namespace ThrashEngine {
	NPC::NPC()
	{
		__virtualization_level = VirtualLevelNPC;
		target = nullptr;
		enableAI = true;

	}
	NPC::~NPC()
	{

	}
	ResultState NPC::Update(double timestep)
	{
		if (enableAI)
		{
			if (!target) //find target
			{

				std::list<Object*>* ptr = &m_managerPtr->objects;
				for (auto i = ptr->begin(); i != ptr->end(); i++)
				{
					//Chase and attack 
				/*	if (*i != this &&  //Not the same obj
						((Object*)(*i))->GetVirtualState() != ThrashEngine::VirtualLevelObject && //Is NPC
						((NPC*)(*i))->properties.fraction != properties.fraction) //Different fractions
					{
						if (ThrashEngine::DistanceSq(this, *i) < properties.range*properties.range)
						{
							target = (NPC*)(*i);
						}
					}*/
				}
			}
			if (target)
			{
			/*	if (ThrashEngine::(this, target) > properties.range*properties.range)
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
				}*/
			}
			else
			{
			//	m_vel -= m_vel*properties.breakSpeed;
			//	if (m_vel.LenSq() < 1) m_vel = Vector(0, 0);
			}
		}

		AnimationObject::Update(timestep);
		return ResultState::Success;
	}
	ResultState NPC::Draw(Graphics* graphics, double offx, double offy)
	{
		AnimationObject::Draw(graphics, offx, offy);

		//Health bar
		/*if (properties.maxhp) {
			graphics->SetColor(255, 0, 0, 255);
			graphics->DrawRect(m_pos.x + offx, m_pos.y - 10 + offy, m_pos.w + 1, 10);
			graphics->SetColor(0, 255, 0, 255);
			graphics->DrawRect(m_pos.x + offx, m_pos.y - 10 + offy, m_pos.w*((properties.hp + 1) / properties.maxhp), 10);
		}*/
		return ResultState::Success;
	}
	ResultState NPC::Update(Object* object, int event)
	{
		if (__virtualization_level == VirtualLevelNPC)
		{
			if (m_property->GetDouble("TimeBetweenJump") < 60)
			{
				m_property->Set("CanJump", 0);
				//timeJump = 0;
			}
		}
		if (object->GetVirtualState() == VirtualLevelNPC)
		{

		}
		return ResultState::Success;
	}
	void NPC::EnableAI(bool flag)
	{
		enableAI = flag;
	}

}