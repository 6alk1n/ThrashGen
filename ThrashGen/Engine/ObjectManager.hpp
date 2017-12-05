#pragma once
/***********
//ObjectManager.hpp Container for objects (inherits from SpriteManager)
**************/
#include "Object.hpp"

namespace ThrashEngine
{
	const int UpdateEventCollision = 1;
	struct Collision
	{
		Object* obj1;
		Object* obj2;
	};

	class ObjectManager
	{
	public:
		//Methods
		ObjectManager();
		~ObjectManager();
		void AddObject(Object*);
		ResultState Draw(Graphics* graphics,double offx=0,double offy=0);
		ResultState Update(double timedelta);
		int HandleCollision(Object*, Object*);
		int HandleRectCollision(Object*, Object*);
		Object* Get(unsigned int, unsigned int, unsigned int);
		Object* Get(unsigned int, unsigned int);
		Object* Get(unsigned int);
		bool Set(unsigned int, unsigned int, unsigned int);
		bool Set(unsigned int, unsigned int, Object*);
		void Clear();

		//Members
		std::list<Object*> objects;
		std::list<Object*>** tilemap;
		std::list<Collision> collisions;
		unsigned int TileMapWidth;
		unsigned int TileMapHeight;
		bool TileMapActive;
		PropertyClass m_property;
	protected:
		unsigned int objectID;

	};/*
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
	*/
}