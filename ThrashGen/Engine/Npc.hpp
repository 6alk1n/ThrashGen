#pragma once
#pragma once
#include "Object.hpp"
#include "ObjectManager.hpp"
#include "Animation.hpp"
#include <map>
namespace ThrashEngine {

	enum NPCState
	{
		Idle,
		Moving,
		Attack,
		Chacing,
		Jump,
		Kill
	};

	enum PropertyType
	{
		INT,
		DOUBLE,
		CHAR,
		BOOL,
		STRING,
		ERRORTYPE
	};

	struct NPCProperty
	{
		NPCProperty()
		{
			type = ERRORTYPE;
			data = nullptr;
		}
		PropertyType type;
		void* data;
	};

	struct NPCProperties
	{
		int fraction;
		NPCState state;
		double range;
		double InteractionRange;
		double MaxSpeed;
		double Acceleration;
		double breakSpeed;
		double interactionColdDown;
		double hp;
		double maxhp;
		double damage;
		double armor;
	};

	const int VirtualStateNPC = 2;
	const int VirtualStatePlayer = 4;


	const int UpdateEventInteraction = 2;


	class NPC : public AnimationObject
	{
	public:
		NPC();
		virtual ~NPC();
		virtual ResultState Update() override;
		virtual ResultState Update(Object*, int) override;
		virtual ResultState Draw(Graphics*, double offx = 0, double offy = 0);
		NPCProperties properties;
		void EnableAI(bool);
		bool canJump;
		double timeBetweenJump;
		NPCProperty GetProperty(std::string);
		NPCProperty SetProperty(std::string, NPCProperty);
		NPCProperty SetProperty(std::string, double);
		NPCProperty SetProperty(std::string, std::string);
		NPCProperty SetProperty(std::string, char);
		NPCProperty SetProperty(std::string, bool);
		std::map<std::string, NPCProperty> m_property;
	protected:
		NPC* target;
		bool enableAI;
		double timeJump;
		double timelastattack;
	};

	static 	NPC* CreateNPC(std::string SpriteHeaderName, ObjectManager* manager)
	{
		//find spriteheader
		SpriteHeader* head = 0;
		bool found = false;
		int id = 0;
		for (auto i = manager->GetSpriteHeaders()->begin(); i != manager->GetSpriteHeaders()->end(); i++)
		{
			if (i[0]->m_SpriteName == SpriteHeaderName)
			{
				found = true;
				head = i[0];
				break;
			}
			id++;
		}
		if (!found)return nullptr;
		NPC* newSprite = new NPC();
		newSprite->SetTexture(head->m_texture);
		newSprite->SetUV((int)head->m_u, (int)head->m_v, (int)head->m_uend, (int)head->m_vend);
		newSprite->SetSize(head->m_width, head->m_height);
		manager->GetSpritePtr()->push_back(newSprite);
		newSprite->SetID(id);

		manager->AddObject(newSprite);

		newSprite->SetName(SpriteHeaderName);
		return newSprite;
	}

	static NPC* CreateNPC(int id, ObjectManager* manager)
	{

		// find spriteheader
		SpriteHeader* head = (*manager->GetSpriteHeaders())[id];
		NPC* newSprite = new NPC();
		newSprite->SetTexture(head->m_texture);
		newSprite->SetUV((int)head->m_u, (int)head->m_v, (int)head->m_uend, (int)head->m_vend);
		newSprite->SetSize(head->m_width, head->m_height);
		manager->GetSpritePtr()->push_back(newSprite);
		newSprite->SetID(id);
		manager->AddObject(newSprite);
		return newSprite;
	}
}