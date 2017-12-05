#include "GUI.hpp"
#include "Physics.hpp"
namespace ThrashEngine {

	GUI::GUI()
	{
		m_GUIActiveObject = nullptr;
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
		int activeclick = 0;
		for (auto i = m_GUIObjects.begin(); i != m_GUIObjects.end(); i++)
		{
			int gui_event = 0;
			Rectangle guirect = Rectangle(i[0]->GetPos(), Vector(i[0]->m_pos.w, i[0]->m_pos.h));
			if (isPointinRect(m_input->GetMousePos(), guirect))
			{
				gui_event |= EventMouseIn;
				if (m_input->OnDown(MOUSE_LEFT))
				{
					gui_event |= EventMouseClickLeft;
					m_GUIActiveObject = *i;
					activeclick = 1;
				}
				else
				{
				//	m_GUIActiveObject = nullptr;
				}
				if (m_input->IsPressed(MOUSE_LEFT))
				{
					gui_event |= EventMouseOnClickLeft;
				}
			}
			else
			{
				gui_event |= EventMouseOut;
				if (m_input->OnDown(MOUSE_LEFT))
				{
				//	m_GUIActiveObject = nullptr;
				}
			}
			if (m_input->OnDown(MOUSE_LEFT) && !activeclick)
			{
				m_GUIActiveObject = nullptr;
			}

			i[0]->Update(gui_event, timedelta);
			if (m_GUIActiveObject) {
				std::list<int> keys = m_input->GetPressedKeys();
				for (auto i = keys.begin(); i != keys.end(); i++)
				{
					m_GUIActiveObject->UpdateInput(*i);
				}
				m_input->ClearPressedKeys();
			}
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

	void GUI::SetActiveGUIObject(GUIObject* obj)
	{
		m_GUIActiveObject = obj;
	}
}