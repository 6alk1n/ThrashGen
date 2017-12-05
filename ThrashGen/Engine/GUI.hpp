#pragma once
#include "Graphics.hpp"
#include "Input.hpp"
#include "GUIObject.hpp"
#include <vector>
namespace ThrashEngine
{
	class GUI
	{
	public:
		GUI();
		~GUI();
		void SetGraphics(Graphics*);
		void SetInput(Input*);
		void Draw();
		void Update(double);
		void AddGUIObject(GUIObject*);
	protected:
		Graphics* m_graphicsPtr;
		Input* m_input;
		std::vector<GUIObject*> m_GUIObjects;
	
	};
}