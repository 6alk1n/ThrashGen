#include "ObjectManager.hpp"
#include "Physics.hpp"
namespace ThrashEngine {
	ObjectManager::ObjectManager()
	{

	}
	ObjectManager::~ObjectManager()
	{

	}
	Object* ObjectManager::CreateObject(std::string SpriteHeaderName)
	{
		//find spriteheader
		SpriteHeader* head;
		bool found = false;
		int id = 0;
		for (auto i = m_SpriteHeaders.begin(); i != m_SpriteHeaders.end(); i++)
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
		Object* newSprite = new Object();
		newSprite->SetTexture(head->m_texture);
		newSprite->SetUV((int)head->m_u, (int)head->m_v, (int)head->m_uend, (int)head->m_vend);
		newSprite->SetSize(head->m_width, head->m_height);
		m_SpritePtr.push_back(newSprite);
		m_SpriteCount++;
		newSprite->m_SpriteID = id;

		newSprite->m_managerPtr = this;
		newSprite->SetName(SpriteHeaderName);
		return newSprite;
	}
	Object* ObjectManager::CreateObject(int id)
	{
		// find spriteheader
		SpriteHeader* head = m_SpriteHeaders[id];
		Object* newSprite = new Object();
		newSprite->SetTexture(head->m_texture);
		newSprite->SetUV((int)head->m_u, (int)head->m_v, (int)head->m_uend, (int)head->m_vend);
		newSprite->SetSize(head->m_width, head->m_height);
		m_SpritePtr.push_back(newSprite);
		m_SpriteCount++;
		newSprite->m_SpriteID = id;
		newSprite->m_managerPtr = this;
		return newSprite;
	}
	ResultState ObjectManager::Draw(Graphics* graphics)
	{
		for (auto i = m_SpritePtr.begin(); i != m_SpritePtr.end(); i++)
		{
			if ((*i)->Draw(graphics) == ResultState::Fail) return ResultState::Fail;
		}
		return ResultState::Success;
	}
	ResultState ObjectManager::Update(double timedelta)
	{
		/*for (auto i = m_SpritePtr.begin(); i != m_SpritePtr.end(); i++)
		{
			if ((*i)->Update() == ResultState::Fail) return ResultState::Fail;
		}*/
		Rectangle rectA;
		Rectangle rectB;
		for (auto i = m_SpritePtr.begin(); i != m_SpritePtr.end(); i++)
		{
			i[0]->Update();
		/*	for (auto n = i + 1; n != m_SpritePtr.end(); n++)
			{
			
				rectA.x = i[0]->GetX();
				rectA.y = i[0]->GetY();
				rectA.w = i[0]->GetWidth();
				rectA.h = i[0]->GetHeight();

				
				rectB.x = n[0]->GetX();
				rectB.y = n[0]->GetY();
				rectB.w = n[0]->GetWidth();
				rectB.h = n[0]->GetHeight();
				
				if (RectRectCollision(rectA, rectB))
				{
					Object *obji = (Object*)*i;
					Object *objn = (Object*)*n;

					obji->SetVel(-obji->GetVel());
					objn->SetVel(-objn->GetVel());

				}

			}*/
		}

		return ResultState::Success;
	}
	int ObjectManager::GetObjectCount()
	{
		return m_SpriteCount;
	}
	void ObjectManager::AddObject(Object* obj)
	{
	//	m_SpritePtr.push_back(obj);
		m_SpriteCount++;
		obj->m_managerPtr = this;
	}
}