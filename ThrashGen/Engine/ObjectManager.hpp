#pragma once
/***********
//ObjectManager.hpp Container for objects (inherits from SpriteManager)
**************/
#include "SpriteManager.hpp"
#include "Object.hpp"
namespace ThrashEngine
{
	class ObjectManager : public SpriteManager
	{
	public:
		ObjectManager();

		~ObjectManager();
		ResultState Draw(Graphics* graphics);
		ResultState Update(double timedelta);
		Object* CreateObject(std::string); //Create Sprite with SpriteHeader and put its address in vector
		Object* CreateObject(int); //Create Sprite with SpriteHeader and put its address in vector
		void AddObject(Object*);
		int GetObjectCount();

	protected:
	};
}