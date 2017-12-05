#pragma once
#include "Object.hpp"

namespace ThrashEngine
{

	struct Animation
	{
		std::string animName;
		int startAnim;
		int endAnim;
		double frameTime;
		bool loop;
	};

	class AnimationObject :public Object
	{
	public:
		AnimationObject();
		virtual ~AnimationObject();
		void AddAnimation(Animation);
		void SetUVCell(int, int);
		void SetAnimation(std::string);
		virtual ResultState Update();
		virtual ResultState Draw(Graphics*, double , double);

	protected:
		Animation* GetAnim(std::string);
		std::vector<Animation> m_animations;
		Animation* m_currentAnim;
		int m_frameNum;
		int m_uvCellWidth;
		int m_uvCellHeight;
		int m_uvColumn;
		int m_uvRow;
		int m_loopCount;
		double m_timeAnimPassed;
	};
}