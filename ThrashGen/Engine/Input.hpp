#pragma once
#include "Core.hpp"
/*
Input class is basicaly a cache with functions.
*/
namespace ThrashEngine
{
	//Type for telling what state of key is now
	enum KeyState
	{
		Up,
		Pressed,
		Down,
		Released
	};

	const int MOUSE_LEFT = 256;
	const int MOUSE_RIGHT = 258;
	const int MOUSE_MIDDLE = 267;

	class Input
	{
	public:
		Input();
		~Input();
		bool IsPressed(int key); //checks if pressed button (down or pressed)
		bool OnDown(int key);//checks keyondown event
		bool OnUp(int key);//checks keyonup event
		KeyState GetKey(int key);//get key state
		void Update(); //Updated all keys (down->pressed  up->released)
		void Press(int key);//press key
		void Release(int key);//release key
		void SetMousePos(Vector pos);//set mouse pos
		void SetMousePos(int x, int y);//set mouse pos
		void SetDelta(int x, int y);
		int GetDeltaX();
		int GetDeltaY();
		//Getters
		int GetMouseX();
		int GetMouseY();
		Vector GetMousePos();
	protected:
		KeyState keys[256 + 5];
		int mousex, mousey;
		int deltax, deltay;

	};
}