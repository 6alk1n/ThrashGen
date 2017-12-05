#pragma once

#include "Animation.hpp"
namespace ThrashEngine
{
	class AnimationFactory
	{
	public:
		Animation* GetAnimation(std::string);
		AnimationList* GetAnimationInstance(std::string);
		int AddAnimation(std::string, Animation*);
		int AddAnimation(std::string, int, int, double);
		int CreateInstance(std::string);
		int AddAnimationToInstance(std::string, std::string,Animation*);
		int AddAnimationToInstance(std::string, std::string);
	public:
		std::map<std::string, AnimationList*> m_animationInstances;
		std::map<std::string, Animation*> m_anims;
	};
}