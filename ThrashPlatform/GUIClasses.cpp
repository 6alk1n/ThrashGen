#include "GUIClasses.hpp"
//#include <Engine\GUIObject.hpp>
	GUIButton::GUIButton()
	{
		mouseon = false;

	}
	GUIButton::~GUIButton()
	{
		ThrashEngine::GUIObject::~GUIObject();
	}
	ThrashEngine::ResultState GUIButton::Update(int events, double timedelta)
	{
		if (!m_active) return ThrashEngine::ResultState::Success;
		if (events&ThrashEngine::EventMouseIn)
		{
			mouseon = true;
		}
		else mouseon = false;
		if (events&ThrashEngine::EventMouseClickLeft) //call on left click
		{
				(*m_functionPtr)(m_data);
		}
		return ThrashEngine::ResultState::Success;
	}
	ThrashEngine::ResultState GUIButton::Draw(ThrashEngine::Graphics* graphics)
	{
		if (!m_active) return ThrashEngine::ResultState::Success;
			Object::Draw(graphics, 0, 0);
		if (mouseon)
		{
			graphics->SetColor(255, 0, 255, 255);
					graphics->DrawRectOut(m_x, m_y, m_width, m_height);
		}
		return ThrashEngine::ResultState::Success;
	}
	void GUIButton::SetBorderColor(SDL_Color color)
	{
		borderColor = color;
	}

	GUISpinButton::GUISpinButton() { timing = 0; }
	GUISpinButton::~GUISpinButton(){}
	ThrashEngine::ResultState GUISpinButton::Update(int events, double deltatime)
	{
		if (!m_active) return ThrashEngine::ResultState::Success;
		if (events&ThrashEngine::EventMouseIn)
		{
			double x = m_input->GetMouseX();
			mouseonbutton = 0;
			if (x < m_width*(1 - textsizerel) / 2 + m_x) mouseonbutton = 1;
			else if (x > m_x + m_width*(1 - textsizerel) / 2 + m_width*textsizerel) mouseonbutton = 2;
		}
		if (events&ThrashEngine::EventMouseClickLeft) //call on left click
		{
			if (mouseonbutton == 1)
				value -= step;
			if (mouseonbutton == 2)
				value += step;
			if (value < min)value = min;
			if (value > max)value = max;
		}
		else if (events&ThrashEngine::EventMouseOnClickLeft)
		{
			timing += deltatime;
			if (timing > 1) {
				if (mouseonbutton == 1)
					value -= step;
				if (mouseonbutton == 2)
					value += step;
				if (value < min)value = min;
				if (value > max)value = max;
			}
		}
		else 
		{
			timing = 0;
		}
		return ThrashEngine::ResultState::Success;
	}
	ThrashEngine::ResultState GUISpinButton::Draw(ThrashEngine::Graphics* graphics)
	{
		if (!m_active) return ThrashEngine::ResultState::Success;
		text.SetGraphics(graphics);
		text.SetSize(ThrashEngine::Vector(m_width*textsizerel, m_height/2));
		text.SetPos(ThrashEngine::Vector(m_x + m_width*(1 - textsizerel)/2, m_y+m_height/2));
		title.SetGraphics(graphics);
		title.SetSize(ThrashEngine::Vector(m_width*textsizerel, m_height/2));
		title.SetPos(ThrashEngine::Vector(m_x + m_width*(1 - textsizerel)/2, m_y));
		SDL_Color color;
		color.r = color.g = color.g = color.a = 255;
		text.SetColor(color);
		color.r = color.g = color.g = color.a = 200;
		title.SetColor(color);

		//Object::Draw(graphics, 0, 0);
		
		SDL_Rect pos,uv;
		pos.x = m_x;
		pos.y = m_y;
		pos.h = m_height;
		pos.w = m_width*(1 - textsizerel) / 2;
		
		uv.x = m_u;
		uv.y = m_v;
		uv.w = m_uend / 2;
		uv.h = m_vend;

		graphics->DrawTexture(m_texture, &pos, &uv);

		pos.x = m_x + m_width*textsizerel + m_width*(1 - textsizerel) / 2;

		uv.x = m_uend / 2;
		uv.w = m_uend;

		graphics->DrawTexture(m_texture, &pos, &uv);

		if (mouseonbutton==1)
		{
			graphics->SetColor(255, 0, 255, 255);
			graphics->DrawRectOut(m_x, m_y, m_width*(1-textsizerel)/2, m_height);
		}
		else if (mouseonbutton == 2)
		{

			graphics->SetColor(255, 0, 255, 255);
			graphics->DrawRectOut(m_x + m_width*textsizerel + m_width*(1 - textsizerel) / 2, m_y, m_width*(1 - textsizerel) / 2, m_height);
		}
		title.ClearField();
		title << titletext;
		title.Render();
		text.ClearField();
		text.Print(value);
		text.Render();
		return ThrashEngine::ResultState::Success;
	}
	double GUISpinButton::GetValue()
	{
		return value;
	}
	void GUISpinButton::SetValue(double val)
	{
		value = val;
	}
	void GUISpinButton::SetMin(double m)
	{
		min = m;
	}
	void GUISpinButton::SetMax(double m)
	{
		max = m;
	}
	void GUISpinButton::SetStep(double st)
	{
		step = st;
	}
	void GUISpinButton::SetTextSizeRelative(double rel)
	{
		textsizerel = rel;
	}

	void GUISpinButton::SetFont(ThrashEngine::Font* font)
	{
		text.SetFont(font);
		title.SetFont(font);
	}
	void GUISpinButton::SetText(std::string str)
	{
		titletext = str;
	}