#include "GUI.hpp"
#include "Physics.hpp"
namespace ThrashEngine {

	GUI::GUI()
	{

	}
	GUI::~GUI()
	{


	}
	void GUI::SetGraphics(Graphics* gr)
	{
		m_graphicsPtr = gr;
	}
	void GUI::SetInput(Input* in)
	{
		m_input = in;
	}
	void GUI::Update(double timedelta)
	{
		for (auto i = m_GUIObjects.begin(); i != m_GUIObjects.end(); i++)
		{
			int gui_event = 0;
			Rectangle guirect = Rectangle(i[0]->GetPos(), Vector(i[0]->GetWidth(), i[0]->GetHeight()));
			if (isPointinRect(m_input->GetMousePos(), guirect))
			{
				gui_event |= EventMouseIn;
				if (m_input->OnDown(MOUSE_LEFT))
				{
					gui_event |= EventMouseClickLeft;
				}
				if (m_input->IsPressed(MOUSE_LEFT))
				{
					gui_event |= EventMouseOnClickLeft;
				}
			}
			else
			{
				gui_event |= EventMouseOut;
			}
			i[0]->Update(gui_event, timedelta);
		}
	}
	void GUI::Draw()
	{
		for (auto i = m_GUIObjects.begin(); i != m_GUIObjects.end(); i++)
			i[0]->Draw(m_graphicsPtr);
	}
	void GUI::AddGUIObject(GUIObject* obj)
	{
		m_GUIObjects.push_back(obj);
		obj->SetInput(m_input);
	}
}