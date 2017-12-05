#include "ObjectFactory.hpp"
namespace ThrashEngine
{
	int ObjectFactory::AddNewObject(std::string objectName, Object* object)
	{
		if (object == nullptr) return -1;
		auto it = m_objectInstances.find(objectName);
		if (it != m_objectInstances.end())
		{
			it->second = object;
			return 1;
		}
		m_objectInstances.insert({ objectName,object });
		return 0;
	}
	Object* ObjectFactory::CreateObject(std::string objectName)
	{
		auto it = m_objectInstances.find(objectName);
		if (it != m_objectInstances.end())
		{
			Object* newNPC = new Object(*it->second);
			newNPC->m_objectName = objectName;
			return newNPC;//Object was created
		}
		return nullptr;
	}
	void ObjectFactory::Clear()
	{
		for (auto i = m_objectInstances.begin(); i != m_objectInstances.end(); i++)
		{
			delete i->second;
		}
		m_objectInstances.clear();
	}
	int AnimationObjectFactory::AddNewAnimationObject(std::string objectName, AnimationObject* object)
	{
		if (object == nullptr) return -1;
		auto it = m_animobjectInstances.find(objectName);
		if (it != m_animobjectInstances.end())
		{
			it->second = object;
			return 1;
		}
		m_animobjectInstances.insert({ objectName,object });
		return 0;
	}
	AnimationObject* AnimationObjectFactory::CreateAnimationObject(std::string objectName)
	{
		auto it = m_animobjectInstances.find(objectName);
		if (it != m_animobjectInstances.end())
		{
			AnimationObject* newNPC = new AnimationObject(*it->second);
			newNPC->m_objectName = objectName;
			return newNPC;//Object was created
		}
		return nullptr;
	}
	int AnimationObjectFactory::SetAnimations(AnimationFactory* factory)
	{
		if (!factory) return 0;
		for (auto i = m_animobjectInstances.begin(); i != m_animobjectInstances.end(); i++)
		{
			if (i->second->m_animlistname!="") {
				AnimationList* list = factory->GetAnimationInstance(i->second->m_animlistname);
				if (list)
					i->second->SetAnimation(list, i->second->m_animlistname);
			}
		}
		return 1;
	}
	void AnimationObjectFactory::Clear()
	{
		for (auto i = m_animobjectInstances.begin(); i != m_animobjectInstances.end(); i++)
		{
			delete i->second;
		}
		m_animobjectInstances.clear();
	}
	int NpcFactory::AddNewNpc(std::string objectName, NPC* object)
	{
		if (object == nullptr) return -1;
		auto it = m_npcInstances.find(objectName);
		if (it != m_npcInstances.end())
		{
			it->second = object;
			return 1;
		}
		m_npcInstances.insert({ objectName,object });
		return 0;
	}
	NPC* NpcFactory::CreateNpc(std::string objectName)
	{
		auto it = m_npcInstances.find(objectName);
		if (it != m_npcInstances.end())
		{
			NPC* newNPC = new NPC(*it->second);
			newNPC->m_objectName = objectName;
			return newNPC;//Object was created
		}
		return nullptr;
	}	
	int NpcFactory::SetAnimations(AnimationFactory* factory)
	{
		if (!factory) return 0;
		for (auto i = m_npcInstances.begin(); i != m_npcInstances.end(); i++)
		{
			if (i->second->m_animlistname != "") {
				AnimationList* list = factory->GetAnimationInstance(i->second->m_animlistname);
				if (list)
				{
					i->second->SetAnimation(list, i->second->m_animlistname);
				}
			}
		}
		return 1;
	}
	void NpcFactory::Clear()
	{
		for (auto i = m_npcInstances.begin(); i != m_npcInstances.end(); i++)
		{
			delete i->second;
		}
		m_npcInstances.clear();
	}
}