#pragma once
#pragma once
#include "Object.hpp"
#include "ObjectManager.hpp"
#include "Animation.hpp"
#include <map>
namespace ThrashEngine {

	const int VirtualLevelNPC = VirtualLevelAnimationObject+1;
	const int VirtualLevelPlayer = VirtualLevelNPC +1;


	const int UpdateEventInteraction = 2;

	class NPC : public AnimationObject
	{
	public:
		NPC();
		virtual ~NPC();
		virtual ResultState Update(double) override;
		virtual ResultState Update(Object*, int) override;
		virtual ResultState Draw(Graphics*, double offx = 0, double offy = 0);
		void EnableAI(bool);
	protected:
		Object* target;
		bool enableAI;

	};
	/*
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
		newSprite->m_textureUV=Rectangle((int)head->m_u, (int)head->m_v, (int)head->m_uend, (int)head->m_vend);
		newSprite->SetSize(head->m_width, head->m_height);
		manager->GetSpritePtr()->push_back(newSprite);
		//newSprite->SetID(id);

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
		newSprite->m_textureUV=Rectangle((int)head->m_u, (int)head->m_v, (int)head->m_uend, (int)head->m_vend);
		newSprite->SetSize(head->m_width, head->m_height);
		manager->GetSpritePtr()->push_back(newSprite);
		//newSprite->SetID(id);
		manager->AddObject(newSprite);
		return newSprite;
	}*/
}