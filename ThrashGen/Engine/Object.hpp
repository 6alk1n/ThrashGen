#pragma once
/**********
Object - advanced object of sprite. Instead of drawing can handle interactions with other objects or world (velocity, collisions)
***********/
#include "Sprite.hpp"
#include <string>



//!!!NEW SYSTEM!!!
namespace ThrashEngine {
  const int VirtualLevelObject= VirtualLevelSprite+1;
  class ObjectManager;
  class Object : public Sprite
  {
    public:
	  //Methods
	  Object();  
	  Object(Sprite*);
	  virtual ~Object();
	  virtual ResultState Draw(Graphics*, double offx=0, double offy=0);
	  virtual ResultState Update(Object*,int);
	  virtual ResultState Update(double);
	  unsigned int GetVirtualizationLevel();

	  //Members
	  Vector m_vel;
	  bool m_active;
	  bool m_collideable;
	  bool m_debug;
	  bool m_static;
	  PropertyClass* m_property;
	  unsigned int m_objectID;

	  ObjectManager* m_managerPtr;
	  friend class ObjectManager;
	  std::string m_objectName;
  };
}


/*
namespace ThrashEngine {
	const int VirtualStateObject = 1;
	const int VirtualStateGUIObject = 3;
	class ObjectManager;
	class Object :public Sprite
	{
	public:
		Object();
		Object(Sprite*);
		virtual ~Object();
		ResultState SetVel(double x,double y);
		ResultState SetVel(Vector v);
		ResultState Force(double x, double y); //Add force
		ResultState Force(Vector v); //Add force
		void AddVelocity(double x, double y);
		void AddVelocity(Vector v);
		void SetVelX(double x);
		void SetVelY(double y);
		ResultState SetForce(double x, double y);
		ResultState SetForce(Vector v);
		ResultState SetForceX(double x);
		ResultState SetForceY(double y);
	
		Vector GetForce();
		Vector GetVel();
		virtual ResultState Update();
		virtual ResultState Update(Object*,int);
		virtual ResultState Draw(Graphics*, double offx=0, double offy=0 );

		bool IsActive();
		bool IsCollideable();
		void SetCollision(bool);
		void SetActive(bool);

		bool m_static; //is object static(doesn't move)
		int GetVirtualState();
		void SetVirtualState(int);
		void SetDebugDraw(bool);

		void SetName(std::string str);
		std::string GetName();
	protected:
		Vector m_vel;   //forever velocity
		Vector m_force; //one time velocity
		bool m_active;  //needs to update
		bool m_collideable; //needs to collide
		bool m_debugDraw;
		int m_virtualState;
		ObjectManager* m_managerPtr;
		friend class ObjectManager;

		std::string m_name;

	};

	static double DistanceSq(Sprite* a, Sprite* b)
	{
		Vector vec = a->m_pos.GetVector() - b->m_pos.GetVector();
		return vec.LenSq();
	}
}
*/