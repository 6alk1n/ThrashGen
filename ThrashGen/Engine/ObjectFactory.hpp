#pragma once
#include "Npc.hpp"
#include "AnimationFactory.hpp"

namespace ThrashEngine
{
	class ObjectFactory
	{
	public:
		int AddNewObject(std::string, Object*);
		Object* CreateObject(std::string);
		void Clear();
	public:
		std::map<std::string, Object*> m_objectInstances;
	};

	class AnimationObjectFactory
	{
	public:
		int AddNewAnimationObject(std::string, AnimationObject*);
		AnimationObject* CreateAnimationObject(std::string);
		int SetAnimations(AnimationFactory*);
		void Clear();
	public:
		std::map<std::string, AnimationObject*> m_animobjectInstances;
	};	
	class NpcFactory
	{
	public:
		int AddNewNpc(std::string, NPC*);
		NPC* CreateNpc(std::string);
		int SetAnimations(AnimationFactory*);
		void Clear();
	public:
		std::map<std::string, NPC*> m_npcInstances;
	};
}