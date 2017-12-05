#include "Input.hpp"
namespace ThrashEngine
{
	Input::Input()
	{
		for (int i = 0; i < 256 + 5; i++)
		{
			keys[i] = KeyState::Released;
		}
		mousex = mousey = 0;
	}
	Input::~Input()
	{

	}
	bool Input::IsPressed(int key)
	{
		return (keys[key] == KeyState::Pressed || keys[key] == KeyState::Down);
	}
	bool Input::OnDown(int key)
	{
		return (keys[key] == KeyState::Down);
	}
	bool Input::OnUp(int key)
	{

		return (keys[key] == KeyState::Up);
	}
	KeyState Input::GetKey(int key)
	{
		return keys[key];
	}
	void Input::Update()
	{
		for (int i = 0; i < 256 + 5; i++)
		{
			if (keys[i] == KeyState::Down) keys[i] = KeyState::Pressed;
			if (keys[i] == KeyState::Up) keys[i] = KeyState::Released;
		}
		deltax = deltay = 0;
	}
	void Input::Press(int key)
	{
		if(keys[key]!=KeyState::Pressed) keys[key] = KeyState::Down;
	}

	void Input::Release(int key)
	{
		if (keys[key] != KeyState::Released) keys[key] = KeyState::Up;
	}

	void Input::SetMousePos(Vector pos)
	{
		deltax = pos.x - mousex;
		deltay = pos.y - mousey;
		mousex = (int)pos.x;
		mousey = (int)pos.y;
	}
	void Input::SetMousePos(int x, int y)
	{
		deltax = x - mousex;
		deltay = y - mousey;
		mousex = x;
		mousey = y;
	}
	int Input::GetMouseX()
	{
		return mousex;
	}
	int Input::GetMouseY()
	{
		return mousey;
	}
	Vector Input::GetMousePos()
	{
		return Vector(mousex, mousey);
	}
	void Input::SetDelta(int x, int y)
	{
		deltax = x;
		deltay = y;
	}
	int Input::GetDeltaX()
	{
		return deltax;
	}
	int Input::GetDeltaY()
	{
		return deltay;
	}
}