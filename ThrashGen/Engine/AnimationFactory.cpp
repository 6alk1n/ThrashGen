#include "AnimationFactory.hpp"
namespace ThrashEngine {
	Animation* AnimationFactory::GetAnimation(std::string animName) 
	{
		auto it = m_anims.find(animName);
		if (it != m_anims.end())
		{
			return it->second; //Animation was found
		}
		return nullptr;
	}
	AnimationList* AnimationFactory::GetAnimationInstance(std::string animName)
	{
		auto it = m_animationInstances.find(animName);
		if (it != m_animationInstances.end())
		{
			return it->second; //Animation was found
		}
		return nullptr;
	}
	int AnimationFactory::AddAnimation(std::string animName, Animation* anim) 
	{
		if (anim == nullptr) return -1;
		auto it = m_anims.find(animName);
		if (it != m_anims.end())
		{
			it->second = anim;
			return 1;
		}
		m_anims.insert({ animName,anim });
		return 0;
	}
	int AnimationFactory::AddAnimation(std::string animName, int startFrame, int endFrame, double frameTime)
	{
		Animation* newAnim = new Animation;
		newAnim->startAnim = startFrame;
		newAnim->endAnim = endFrame;
		newAnim->frameTime = frameTime;
		return AddAnimation(animName, newAnim);
	}
	int AnimationFactory::CreateInstance(std::string listName)
	{
		if (listName == "") return -1;
		AnimationList* newlist = new AnimationList;
		auto it = m_animationInstances.find(listName);
		if (it != m_animationInstances.end())
		{
			it->second = newlist;
			return 1;
		}
		m_animationInstances.insert({ listName,newlist });
		return 0;
	}
	int AnimationFactory::AddAnimationToInstance(std::string listName, std::string animName, Animation* addAnim)
	{
		if (addAnim == nullptr) return 0;
		AnimationList* list = GetAnimationInstance(listName);
		if (list)
		{
			list->Set(animName, addAnim);
		}
		else
		{
			CreateInstance(listName);
			list = GetAnimationInstance(listName);  
			list->Set(animName, addAnim);
		}
		return 1;
	}
	int AnimationFactory::AddAnimationToInstance(std::string listName, std::string animName)
	{
		AnimationList* list = GetAnimationInstance(listName);
		if (list)
		{
			Animation* anim = GetAnimation(animName);
			if (anim)
			{
				list->Set(animName, anim);
				return 1;
			}
			else return 0;
		}
		else
		{
			Animation* anim = GetAnimation(animName);
			if (anim)
			{
				list->Set(animName, anim);
				return 1;
			}
			else return 0;
		}
	}
}