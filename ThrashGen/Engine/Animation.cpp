#include "Animation.hpp"
namespace ThrashEngine {


	Animation* AnimationList::Get(std::string animName)
	{
		auto it = m_anims.find(animName);
		if (it != m_anims.end())
		{
			return it->second; //Animation was found
		}
		return nullptr;
	}
	int AnimationList::Set(std::string animName, Animation* newAnim)
	{
		auto it = m_anims.find(animName);
		if (it != m_anims.end())
		{
			it->second = newAnim;
			return 1;
		}
		m_anims.insert({ animName,newAnim });
		return 0;
	}


	AnimationObject::AnimationObject():Object()
	{
		m_animation = new AnimationList;
		m_currentAnimation = nullptr;
		m_timePassed = m_currentFrame = 0;
		m_loopCount = 0;
		__virtualization_level = VirtualLevelAnimationObject;
	}
	AnimationObject::~AnimationObject(){}
	void AnimationObject::AddAnimation(Animation* anim, std::string animName)
	{	
		m_animation->Set(animName, anim);
	}
	void AnimationObject::SetAnimationUV(Rectangle rect)
	{
		int w, h;
		m_animUV.x=rect.x;
		m_animUV.y=rect.y;

		SDL_QueryTexture(m_texture, NULL, NULL, &w, &h);
		m_animUV.w = w / m_animUV.x;		
		m_animUV.h = h / m_animUV.y;
	}
	void AnimationObject::SetAnimation(AnimationList* list,std::string listname)
	{
		m_animation = list;
		m_animlistname = listname;
	}
	ResultState AnimationObject::Update(double timestep=1.0)
	{
		m_timePassed+=timestep;
		if (m_currentAnimation && m_timePassed > m_currentAnimation->frameTime)
		{
			if (m_currentAnimation->startAnim != m_currentAnimation->endAnim) {
				if (m_currentFrame >= m_currentAnimation->endAnim)
				{
					if (m_loopAnimation) {
						m_currentFrame = m_currentAnimation->startAnim;
						m_loopCount++;
					}
				}
				else
				{
					m_currentFrame++;
					m_timePassed = 0;
				}
			}
		}
		Object::Update(timestep);
		return ResultState::Success;
	}
	/*Animation* AnimationObject::GetAnim(std::string animName)
	{
		for (auto i = m_animations.begin(); i != m_animations.end(); i++)
		{
			if (i[0].animName == animName) return &i[0];
		}
		
		return nullptr;
	}*/
	void AnimationObject::SetAnimation(std::string str)
	{
		Animation* newAnimation = m_animation->Get(str);
		if (newAnimation && newAnimation!=m_currentAnimation)
		{
			m_loopCount=0;
			m_currentAnimation = newAnimation;
			m_currentFrame = m_currentAnimation->startAnim;
			m_timePassed = 0;
		}

	}
	/*void AnimationObject::SetAnimationUV(Rectangle animuv)
	{
		m_animUV = animuv;
	}*/
	void AnimationObject::SetAnimationUV(double x , double y, double w, double h)
	{
		m_animUV = Rectangle(x, y, w, h);
	}
	void AnimationObject::SetAnimation(Animation* animation)
	{
		if (animation)
		{
			m_loopCount=0;
			m_currentAnimation = animation;
			m_currentFrame = m_currentAnimation->startAnim;
			m_timePassed = 0;
		}
	}
	ResultState AnimationObject::Draw(Graphics* graphics, double offx = 0, double offy = 0)
	{
		if (m_currentAnimation)
		{
			m_textureUV.x = m_animUV.x*(m_currentFrame%(int)m_animUV.w);
			m_textureUV.w = m_animUV.x;

			m_textureUV.y = m_animUV.y*(m_currentFrame /(int) m_animUV.w);
			m_textureUV.h = m_animUV.y;
		}
		Object::Draw(graphics, offx, offy);

		return ResultState::Success;
	}
}
