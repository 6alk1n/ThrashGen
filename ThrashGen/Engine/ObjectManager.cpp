#include "ObjectManager.hpp"
#include "Physics.hpp"
namespace ThrashEngine {
	ObjectManager::ObjectManager()
	{
		tilemap = nullptr;
		TileMapWidth = TileMapHeight;
		TileMapActive = false;
		objectID = 0;
		m_property.Set("CollisionCurrentTime", 0);
		m_property.Set("CollisionUpdateTime", 0);
	}
	ObjectManager::~ObjectManager()
	{

	}
	void ObjectManager::AddObject(Object* object)
	{
		if (object)
		{
			object->m_objectID = ++objectID;
			object->m_managerPtr = this;
			objects.push_back(object);

		}
	}
	ResultState ObjectManager::Draw(Graphics* graphics,double offx , double offy)
	{
		for (auto i = objects.begin(); i != objects.end(); i++)
		{
			if ((*i)->Draw(graphics,offx,offy) == ResultState::Fail) return ResultState::Fail;
		}
		return ResultState::Success;
	}
	ResultState ObjectManager::Update(double timedelta)
	{
		if (tilemap) {
			for (unsigned int i = 0; i < TileMapWidth*TileMapHeight; i++)
			{
				//	if (m_tiles[i]->GetVel().LenSq() != 0)
				{
					//object moves
				}
				for (auto n = tilemap[i]->begin(); n != tilemap[i]->end(); n++)
				{
					(*n)->Update(timedelta);
				}
			}
		}
		for (auto i = objects.begin(); i != objects.end(); i++)
		{
			(*i)->Update(timedelta);
		}
		for (auto i = objects.begin(); i != objects.end(); i++) {
			auto obj1 = (Object*)(*i);
			if (obj1->m_static || obj1->m_vel.LenSq() == 0) continue;
			for (auto n = objects.begin(); n != objects.end(); n++)
			{
				if (n == i) continue;
				auto obj2 = (Object*)(*n);
				//HandleCollision(obj1, obj2);
				HandleRectCollision(obj1, obj2);
			}
		}

		//update time for clearing collision list
		m_property.Set("CollisionCurrentTime", m_property.GetDouble("CollisionCurrentTime") + timedelta);
		//m_currentupdatetime += delta;
		if ((m_property.GetDouble("CollisionCurrentTime") >= m_property.GetDouble("CollisionUpdateTime")) && m_property.GetDouble("CollisionCurrentTime"))
		{
			collisions.clear();
			m_property.Set("CollisionCurrentTime", 0);
		}

		return ResultState::Success;
	}		
	Object* ObjectManager::Get(unsigned int id)
	{
		for (auto i = objects.begin(); i != objects.end(); i++)
		{
			if ((*i)->m_objectID == id) return *i;
		}
		return nullptr;
	}
	int ObjectManager::HandleCollision(Object* obj1, Object* obj2)
	{
		//AABB collision
		if (RectRectCollisionWeak(obj1->GetRect(), obj2->GetRect()))
		{
			//Collision detected between objects obj1 & obj2

			obj1->Update(obj2, UpdateEventCollision);

			collisions.push_back(Collision{ obj1,obj2 }); //add collision to the vector

															//Handling collision

			bool obj1col = false;
			int i = 0; //find type of collision
			Vector intersectpoints[2]; //describes points that are in object
			int intersectp1 = 0, intersectp2 = 0;

			if (isPointinRect(obj1->GetPos(), obj2->GetRect())) //upper left point is in rect
			{
				intersectpoints[i] = obj1->GetPos();
				i++;
				intersectp1 = 1;
			}
			if (isPointinRect(obj1->GetPos() + Vector(obj1->m_pos.w, 0), obj2->GetRect())) //upper right point
			{
				intersectpoints[i] = obj1->GetPos() + Vector(obj1->m_pos.w, 0);
				i++;
				if (intersectp1) intersectp2 = 2;
				else intersectp1 = 2;
			}
			if (i < 2 && isPointinRect(obj1->GetPos() + Vector(obj1->m_pos.w, obj1->m_pos.h), obj2->GetRect())) //lower right point
			{
				intersectpoints[i] = obj1->GetPos() + Vector(obj1->m_pos.w, obj1->m_pos.h);
				i++;

				if (intersectp1) intersectp2 = 3;
				else intersectp1 = 3;
			}
			if (i < 2 && isPointinRect(obj1->GetPos() + Vector(0, obj1->m_pos.h), obj2->GetRect())) //lower left point
			{
				intersectpoints[i] = obj1->GetPos() + Vector(0, obj1->m_pos.h);
				i++;

				if (intersectp1) intersectp2 = 4;
				else intersectp1 = 4;
			}
			if (i == 0) //obj1>obj2 (obj2 is in obj1 but need to move obj1)
			{
				obj1col = true;
				if (isPointinRect(obj2->GetPos(), obj1->GetRect())) //upper left point is in rect
				{
					intersectpoints[i] = obj2->GetPos();
					i++;
					intersectp1 = 1;
				}
				if (isPointinRect(obj2->GetPos() + Vector(obj2->m_pos.w, 0), obj1->GetRect())) //upper right point
				{
					intersectpoints[i] = obj2->GetPos() + Vector(obj2->m_pos.w, 0);
					i++;
					if (intersectp1) intersectp2 = 2;
					else intersectp1 = 2;
				}
				if (i < 2 && isPointinRect(obj2->GetPos() + Vector(obj2->m_pos.w, obj2->m_pos.h), obj1->GetRect())) //lower right point
				{
					intersectpoints[i] = obj2->GetPos() + Vector(obj2->m_pos.w, obj2->m_pos.h);
					i++;

					if (intersectp1) intersectp2 = 3;
					else intersectp1 = 3;
				}
				if (i < 2 && isPointinRect(obj2->GetPos() + Vector(0, obj2->m_pos.h), obj1->GetRect())) //lower left point
				{
					intersectpoints[i] = obj2->GetPos() + Vector(0, obj2->m_pos.h);
					i++;

					if (intersectp1) intersectp2 = 4;
					else intersectp1 = 4;
				}
			}
			Vector offset(0, 0);
			Vector resultVel = obj1->m_vel;
			if (!obj1col) {
				if (i == 2) //handle collision only on one axis
				{
					if (obj1->m_pos.x <= obj2->m_pos.x + obj2->m_pos.w && obj1->m_pos.x >= obj2->m_pos.x
						&&
						obj1->m_pos.x + obj1->m_pos.w <= obj2->m_pos.x + obj2->m_pos.w && obj1->m_pos.x + obj1->m_pos.w >= obj2->m_pos.x) //Y axis handling
					{
						double getUpperborder = abs(intersectpoints[0].y - obj2->m_pos.y); //Get distance from upper border
						double getLowerborder = abs(intersectpoints[0].y - (obj2->m_pos.y + obj2->m_pos.h)); //Get distance from lower border
						double koef = 1.0;
						if (intersectp1 == 1) koef = -1.0;
						if (getUpperborder > getLowerborder) offset += Vector(0, koef*getLowerborder); //summ to offset less distance
						else offset += Vector(0, koef*getUpperborder);
						resultVel.y = 0;
					}
					else //X axis handling
					{
						double getUpperborder = abs(intersectpoints[0].x - obj2->m_pos.x); //Get distance from upper border
						double getLowerborder = abs(intersectpoints[0].x - (obj2->m_pos.x + obj2->m_pos.w)); //Get distance from lower border
						double koef = 1.0;
						if (intersectp1 == 1) koef = -1.0;
						if (getUpperborder > getLowerborder) offset += Vector(koef*getLowerborder, 0); //summ to offset less distance
						else offset += Vector(koef*getUpperborder, 0);
						resultVel.x = 0;
					}
				}
				else //collsion with one axis
				{
					//find the closest point
					Vector closestpoint[4];
					closestpoint[0] = intersectpoints[0] - obj2->GetPos();
					closestpoint[1] = intersectpoints[0] - (obj2->GetPos() + Vector(obj2->m_pos.w, 0));
					closestpoint[2] = intersectpoints[0] - (obj2->GetPos() + Vector(obj2->m_pos.w, obj2->m_pos.h));
					closestpoint[3] = intersectpoints[0] - (obj2->GetPos() + Vector(0, obj2->m_pos.h));
					int smallest = 0;
					for (int it = 1; it < 4; it++)
					{
						if (closestpoint[smallest].LenSq() > closestpoint[it].LenSq()) smallest = it;
					}

					if (abs(closestpoint[smallest].x) > abs(closestpoint[smallest].y))
					{
						offset = Vector(0, closestpoint[smallest].y); //set offset to be vector to closest point
						resultVel.y = 0;
					}
					else
					{
						offset = Vector(closestpoint[smallest].x, 0);
						resultVel.x = 0;
					}

				}
			}
			else //same as upper but there can be only two point of intersect (i=2); change obj1 on obj2
			{
				if (obj2->m_pos.x <= obj1->m_pos.x + obj1->m_pos.w && obj2->m_pos.x >= obj1->m_pos.x
					&&
					obj2->m_pos.x + obj2->m_pos.w <= obj1->m_pos.x + obj1->m_pos.w && obj2->m_pos.x + obj2->m_pos.w >= obj1->m_pos.x) //Y axis handling
				{
					double getUpperborder = abs(intersectpoints[0].y - obj1->m_pos.y); //Get distance from upper border
					double getLowerborder = abs(intersectpoints[0].y - (obj1->m_pos.y + obj1->m_pos.h)); //Get distance from lower border
					double koef = 1.0;
					if (intersectp1 == 1) koef = -1.0;
					if (getUpperborder > getLowerborder) offset += Vector(0, koef*getLowerborder); //summ to offset less distance
					else offset -= Vector(0, koef*getUpperborder);
					resultVel.y = 0;
				}
				else //X axis handling
				{
					double getUpperborder = abs(intersectpoints[0].x - obj1->m_pos.x); //Get distance from upper border
					double getLowerborder = abs(intersectpoints[0].x - (obj1->m_pos.x + obj1->m_pos.w)); //Get distance from lower border
					double koef = 1.0;
					//if (intersectp1 == 1) koef = -1.0;
					if (getUpperborder > getLowerborder) offset += Vector(koef*getLowerborder, 0); //summ to offset less distance
					else offset -= Vector(koef*getUpperborder, 0);
					resultVel.x = 0;
				}
			}
			if (!obj1->m_static) obj1->Move(-offset);//Move object 
			obj1->m_vel = resultVel;


		}
		return 1;
	}
	int ObjectManager::HandleRectCollision(Object* obj1, Object* obj2)
	{
		//AABB collision
		if (RectRectCollisionWeak(obj1->GetRect(), obj2->GetRect()))
		{
			//Collision detected between objects obj1 & obj2

			obj1->Update(obj2, UpdateEventCollision);

			collisions.push_back(Collision{ obj1,obj2 }); //add collision to the vector

			  //Handling collision
			bool washandledcollision = false;
			obj1->Move(-obj1->m_vel);
			//if (obj1->m_vel.y > 0 &&( (obj1->m_pos.x<= (obj2->m_pos.x+obj2->m_pos.w)) || (obj1->m_pos.x+obj1->m_pos.w >= obj2->m_pos.x))) //Moving down
			if (obj1->m_vel.y > 0 && (obj1->m_pos.y+ obj1->m_pos.h<=obj2->m_pos.y)) //Moving down
			{
				obj1->Move(obj1->m_vel);
				double off= abs(obj2->m_pos.y - (obj1->m_pos.y + obj1->m_pos.h));
				obj1->m_pos.y -= off;
				obj1->m_vel.y = 0;
				washandledcollision = true;
			}
			else if (obj1->m_vel.x < 0 && (obj1->m_pos.x >= obj2->m_pos.x + obj2->m_pos.w))
			{
				obj1->Move(obj1->m_vel);
				obj1->m_pos.x += abs(obj2->m_pos.x + obj2->m_pos.w - obj1->m_pos.x);
				obj1->m_vel.x = 0;
				washandledcollision = true;
			}
			else if (obj1->m_vel.x > 0 && (obj1->m_pos.x + obj1->m_pos.w <= obj2->m_pos.x))
			{
				obj1->Move(obj1->m_vel);
				obj1->m_pos.x -= abs(obj1->m_pos.x + obj1->m_pos.w - obj2->m_pos.x);
				obj1->m_vel.x = 0;
				washandledcollision = true;
			}
			else if (obj1->m_vel.y < 0 && (obj2->m_pos.y + obj2->m_pos.h <= obj1->m_pos.y))
			{
				obj1->Move(obj1->m_vel);
				double off = abs(obj1->m_pos.y - (obj2->m_pos.y + obj2->m_pos.h));
				obj1->m_pos.y += off;
				obj1->m_vel.y = 0;
				washandledcollision = true;
			}
			if(!washandledcollision) obj1->Move(obj1->m_vel);
		}
		return 1;
	}
	void ObjectManager::Clear()
	{
		for (unsigned int i = 0; i < TileMapWidth*TileMapHeight; i++)
			if (tilemap[i])delete tilemap[i];
		delete[] tilemap;
		for (auto i = objects.begin(); i != objects.end(); i++)
		{
			delete *i;
		}
		objects.clear();
		objectID = 0;
	}
	Object* ObjectManager::Get(unsigned int, unsigned int, unsigned int)
	{
		//empty
		return nullptr;
	}
	Object* ObjectManager::Get(unsigned int, unsigned int)
	{
		//empty
		return nullptr;
	}
	bool ObjectManager::Set(unsigned int, unsigned int, unsigned int)
	{
		//empty
		return false;
	}
	bool ObjectManager::Set(unsigned int, unsigned int, Object*)
	{
		//empty
		return false;
	}
}