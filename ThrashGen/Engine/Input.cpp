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
		m_scaleWidth = m_scaleHeight = 1;
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
		
		m_pressedkeys.clear();
	}
	void Input::Press(int key)
	{
		if (keys[key] == KeyState::Released) m_pressedkeys.push_back(key);
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
	void Input::SetMousePos(double x, double y)
	{
		deltax = x - mousex;
		deltay = y - mousey;
		mousex = x;
		mousey = y;
	}
	double Input::GetMouseX()
	{
		return mousex / m_scaleWidth;
	}
	double Input::GetMouseY()
	{
		return mousey / m_scaleWidth;
	}
	Vector Input::GetMousePos()
	{
		return Vector(mousex / m_scaleWidth, mousey / m_scaleWidth);
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

	std::list<int> Input::GetPressedKeys()
	{
		return m_pressedkeys;
	}
	void Input::ClearPressedKeys()
	{
		m_pressedkeys.clear();
	}

	void Input::SetScale(double scaleWidth, double scaleHeight)
	{
		m_scaleHeight = scaleHeight;
		m_scaleWidth = scaleWidth;
	}
}