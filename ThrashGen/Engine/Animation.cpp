#include "Animation.hpp"
namespace ThrashEngine {
	AnimationObject::AnimationObject():Object()
	{
		m_timeAnimPassed = 0;
		m_loopCount = 0;
	}
	AnimationObject::~AnimationObject(){}
	void AnimationObject::AddAnimation(Animation anim)
	{
		m_animations.push_back(anim);
	}
	void AnimationObject::SetUVCell(int w, int h)
	{
		m_uvCellWidth = w;
		m_uvCellHeight = h;
		SDL_QueryTexture(m_texture, NULL, NULL, &w, &h);
		m_uvColumn = w / m_uvCellWidth;
		m_uvRow = h / m_uvCellHeight;
	}
	ResultState AnimationObject::Update()
	{
		m_timeAnimPassed++;
		if (m_currentAnim && m_timeAnimPassed > m_currentAnim->frameTime)
		{
			if (m_currentAnim->startAnim != m_currentAnim->endAnim) {
				if (m_frameNum > m_currentAnim->endAnim)
				{
					m_loopCount++;
					if (m_currentAnim->loop)
						m_frameNum = m_currentAnim->startAnim;
				}
				else if (m_currentAnim->loop || !m_loopCount)
				{
					m_frameNum++;
					m_timeAnimPassed = 0;
				}
			}
		}
		Object::Update();
		return ResultState::Success;
	}
	Animation* AnimationObject::GetAnim(std::string animName)
	{
		for (auto i = m_animations.begin(); i != m_animations.end(); i++)
		{
			if (i[0].animName == animName) return &i[0];
		}
		
		return nullptr;
	}
	void AnimationObject::SetAnimation(std::string str)
	{
		if (m_currentAnim && m_currentAnim->animName == str) return;
		m_currentAnim = GetAnim(str);
		m_frameNum = m_currentAnim->startAnim;
		m_loopCount = m_timeAnimPassed = 0;
	}
	ResultState AnimationObject::Draw(Graphics* graphics, double offx = 0, double offy = 0)
	{
		if (m_currentAnim)
		{
			m_u = m_uvCellWidth*(m_frameNum%m_uvColumn);
			m_uend = m_uvCellWidth;

			m_v = m_uvCellHeight*(m_frameNum/m_uvColumn);
			m_vend = m_uvCellHeight;
		}
		Object::Draw(graphics, offx, offy);

		return ResultState::Success;
	}
}
