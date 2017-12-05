#pragma once
#include "Object.hpp"



//!!!NEW SYSTEM!!!
namespace ThrashEngine {

	const int VirtualLevelAnimationObject = VirtualLevelObject+1;
  struct Animation
  {
    int startAnim;
	int endAnim;
	double frameTime;
  };

  struct AnimationList
  {
	std::map<std::string, Animation*> m_anims;
	Animation* Get(std::string);
	int Set(std::string,Animation*);
  };

  class AnimationObject : public Object
  {
  public:
    //Methods
    AnimationObject();
	virtual ~AnimationObject();	
	void AddAnimation(Animation*,std::string);
	void SetAnimation(AnimationList*,std::string);
	void SetAnimationUV(Rectangle);
	void SetAnimationUV(double,double,double,double);
	void SetAnimation(std::string);
	void SetAnimation(Animation*);
	virtual ResultState Update(double);
	virtual ResultState Draw(Graphics*, double , double);
	std::string m_animlistname;
	Rectangle m_animUV; 
	bool m_loopAnimation;
  protected:
	//Members
	AnimationList* m_animation;
	Animation* m_currentAnimation;
	unsigned int m_currentFrame;
	double m_timePassed;
	unsigned int m_loopCount;
  };
}

/*
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
}*/