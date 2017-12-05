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
					graphics->DrawRectOut(m_pos.x, m_pos.y, m_pos.w, m_pos.h);
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
			if (x < m_pos.w*(1 - textsizerel) / 2 + m_pos.x) mouseonbutton = 1;
			else if (x > m_pos.x + m_pos.w*(1 - textsizerel) / 2 + m_pos.w*textsizerel) mouseonbutton = 2;
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
		text.SetSize(ThrashEngine::Vector(m_pos.w*textsizerel, m_pos.h/2));
		text.SetPos(ThrashEngine::Vector(m_pos.x + m_pos.w*(1 - textsizerel)/2, m_pos.y+m_pos.h/2));
		title.SetGraphics(graphics);
		title.SetSize(ThrashEngine::Vector(m_pos.w*textsizerel, m_pos.h/2));
		title.SetPos(ThrashEngine::Vector(m_pos.x + m_pos.w*(1 - textsizerel)/2, m_pos.y));
		SDL_Color color;
		color.r = color.g = color.g = color.a = 255;
		text.SetColor(color);
		color.r = color.g = color.g = color.a = 200;
		title.SetColor(color);

		//Object::Draw(graphics, 0, 0);
		
		SDL_Rect pos,uv;
		pos.x = m_pos.x;
		pos.y = m_pos.y;
		pos.h = m_pos.h;
		pos.w = m_pos.w*(1 - textsizerel) / 2;
		
		uv.x = m_textureUV.x;
		uv.y = m_textureUV.y;
		uv.w = m_textureUV.w / 2;
		uv.h = m_textureUV.h;
		
		graphics->DrawTexture(m_texture, &pos, &uv);

		pos.x = m_pos.x + m_pos.w*textsizerel + m_pos.w*(1 - textsizerel) / 2;

		uv.x = m_textureUV.w / 2;
		uv.w = m_textureUV.w;

		graphics->DrawTexture(m_texture, &pos, &uv);

		if (mouseonbutton==1)
		{
			graphics->SetColor(255, 0, 255, 255);
			graphics->DrawRectOut(m_pos.x, m_pos.y, m_pos.w*(1-textsizerel)/2, m_pos.h);
		}
		else if (mouseonbutton == 2)
		{

			graphics->SetColor(255, 0, 255, 255);
			graphics->DrawRectOut(m_pos.x + m_pos.w*textsizerel + m_pos.w*(1 - textsizerel) / 2, m_pos.y, m_pos.w*(1 - textsizerel) / 2, m_pos.h);
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

	GUIInputLabel::GUIInputLabel()
	{
		//m_str = std::string(20, 'c');
		m_str.clear();
		m_text.SetColor(ThrashEngine::Color(255, 255, 255));
		m_resendInputObj = nullptr;
	}
	GUIInputLabel::~GUIInputLabel()
	{

	}
	ThrashEngine::ResultState GUIInputLabel::Update(int events, double deltatime)
	{
		if (!m_activelabel)
		{

		}
		return ThrashEngine::ResultState::Success;
	}
	ThrashEngine::ResultState GUIInputLabel::Draw(ThrashEngine::Graphics* graphics)
	{

		if (!m_activelabel) return ThrashEngine::ResultState::Success;
		m_text.ClearField();
		m_text << m_str;
		m_text.SetPos(ThrashEngine::Vector(m_pos.x, m_pos.y));
		m_text.SetGraphics(graphics);

		graphics->SetColor(m_backcolor);
		graphics->DrawRect(m_pos.x, m_pos.y, m_pos.w, m_pos.h);
		graphics->SetColor(m_bordercolor);
		graphics->DrawRectOut(m_pos.x, m_pos.y, m_pos.w, m_pos.h);

		m_text.Render();

		return ThrashEngine::ResultState::Success;
	}	
	ThrashEngine::ResultState GUIInputLabel::UpdateInput(int key)
	{
		if (!m_activelabel) return ThrashEngine::ResultState::Success;
		if (m_resendInputObj) m_resendInputObj->UpdateInput(key);
		if(key==256 || key =='`' || key == SDL_SCANCODE_LSHIFT || key == 17 || key == 18 || key == 20 || key == 9) return ThrashEngine::ResultState::Success; //0
		if (key == 8) //backspace
		{
			if (m_str.length()>0) m_str.pop_back();
			return ThrashEngine::ResultState::Success;
		}
		if (key==13)
		{
			
			m_result = m_str;
			if (m_str == "")m_result += char(13);
			m_str.clear();
			
			return ThrashEngine::ResultState::Success;
		}
		
		m_text.ClearField();
		bool normsym = true;
		if (key < 0 || key>255) normsym = false;
		if (normsym) {
			if (m_input->IsPressed(SDL_SCANCODE_LSHIFT)) // Shift
			{
				key -= 32;
			}
			unsigned char c = static_cast<unsigned char>(key);
			std::string s(1, c);
			//if (m_input->IsPressed(SDL_SCANCODE_LSHIFT)) // Shift
			{
			//	c += 32;
			}
			m_str += c;
			int i = m_str.length();
			
		}
		return ThrashEngine::ResultState::Success;
	}
	std::string GUIInputLabel::GetInputLabel()
	{
		std::string m_resultback = m_result;
		m_result.clear();
		return m_resultback;
	}

	void GUIInputLabel::SetFont(ThrashEngine::Font* font)
	{
		m_text.SetFont(font);
	}
	void GUIInputLabel::SetActiveLabel(bool f)
	{
		m_activelabel = f;
	}

	void GUIInputLabel::SetBorderColor(SDL_Color col)
	{
		m_bordercolor = col;
	}
	void GUIInputLabel::SetBackgroundColor(SDL_Color col)
	{
		m_backcolor = col;
	}

	void GUIInputLabel::SetTextSize(unsigned int w , unsigned int h)
	{
		m_text.SetLetterSize(w, h);
	}

	void GUIInputLabel::SetResendObj(GUIObject* obj)
	{
		m_resendInputObj = obj;
	}
	GUIDeveloperConsole::GUIDeveloperConsole()
	{
	
		m_inputlabel.m_text.SetColor(ThrashEngine::Color(255, 255, 255));
		m_textinfo.SetColor(ThrashEngine::Color(255, 255, 255));
		m_inputlabel.SetBackgroundColor(ThrashEngine::Color(80, 80, 80));
		m_inputlabel.SetBorderColor(ThrashEngine::Color(90, 90, 90));
		m_inputlabel.SetResendObj(this);
		m_inputlabel.m_text.SetSize(ThrashEngine::Vector(0, 200));
	}
	GUIDeveloperConsole::~GUIDeveloperConsole()
	{
	}
	ThrashEngine::ResultState GUIDeveloperConsole::Update(int, double)
	{
		if (!m_activelabel)
		{

		}
		return ThrashEngine::ResultState::Success;
	}
	ThrashEngine::ResultState GUIDeveloperConsole::Draw(ThrashEngine::Graphics* graphics)
	{

		if (!m_activelabel) return ThrashEngine::ResultState::Success;
		graphics->SetColor(m_backcolor);
		graphics->DrawRect(m_pos.x, m_pos.y, m_pos.w, m_textheight*m_historysizeview);
		graphics->SetColor(m_bordercolor);
		graphics->DrawRectOut(m_pos.x, m_pos.y, m_pos.w, m_textheight*m_historysizeview);

		m_textinfo.ClearField();
		auto n = m_textinfostr.begin();
		for (int i = 0; i < m_currentline; i++)
		{
			if (n == m_textinfostr.end())break;
			n++;
			
		}
		//for (auto i = m_textinfostr.begin(); i != m_textinfostr.end(); i++)
		int count = 0;

		for (; n != m_textinfostr.end(); n++)
		{
			auto i = n;
			m_textinfo << (*i);
			m_textinfo.EndLine();
			count++;
			if (count > m_historysizeview)break;
		}

		m_textinfo.SetPos(ThrashEngine::Vector(m_pos.x, m_pos.y));
		m_textinfo.SetGraphics(graphics);
		m_textinfo.Render();

		m_inputlabel.m_pos = ThrashEngine::Vector (m_pos.x, m_pos.y + m_textheight*m_historysizeview);
		m_inputlabel.SetSize(m_pos.w, m_textheight);
		m_inputlabel.Draw(graphics);

		return ThrashEngine::ResultState::Success;
	}
	ThrashEngine::ResultState GUIDeveloperConsole::UpdateInput(int input)
	{

		if (!m_activelabel) return ThrashEngine::ResultState::Success;
		if (m_input->IsPressed(SDL_SCANCODE_UP))
		{
			if (m_currentline>0) m_currentline--;
		}
		else if (m_input->IsPressed(SDL_SCANCODE_DOWN))
		{
			if (m_currentline<m_historysize-m_historysizeview) m_currentline++;
		}
		else if (m_input->IsPressed(SDL_SCANCODE_PAGEUP))
		{
			if (m_currentline>m_historysizeview) m_currentline-=m_historysizeview;
			else m_currentline = 0;
		}
		else if (m_input->IsPressed(SDL_SCANCODE_PAGEDOWN))
		{
			if (m_currentline < m_textinfostr.size() -(2 * m_historysizeview)) m_currentline += m_historysizeview;
			else m_currentline = m_textinfostr.size();
		}
		
		return ThrashEngine::ResultState::Success;
	}
	bool GUIDeveloperConsole::GetActiveLabel()
	{
		return m_activelabel;
	}
	void GUIDeveloperConsole::SetFont(ThrashEngine::Font* font)
	{
		m_textinfo.SetFont(font);
		m_inputlabel.SetFont(font);
	}
	void GUIDeveloperConsole::SetActiveLabel(bool flag)
	{
		m_activelabel = flag;
		m_inputlabel.SetActiveLabel(flag);
	}
	void GUIDeveloperConsole::SetBorderColor(SDL_Color col)
	{
		m_bordercolor = col;
	}
	void GUIDeveloperConsole::SetBackgroundColor(SDL_Color col)
	{
		m_backcolor = col;
	}
	void GUIDeveloperConsole::SetBorderColorInfo(SDL_Color col)
	{
		m_inputlabel.SetBorderColor(col);
	}
	void GUIDeveloperConsole::SetBackgroundColorInfo(SDL_Color col)
	{
		m_inputlabel.SetBackgroundColor(col);
	}
	void GUIDeveloperConsole::SetTextSize(unsigned int w , unsigned int h)
	{
		m_inputlabel.SetTextSize(w, h);
		m_textinfo.SetLetterSize(w, h);
		m_textheight = h;
	}
	void GUIDeveloperConsole::SetHistorySize(unsigned int size)
	{
		m_historysize = size;	
	}

	void GUIDeveloperConsole::SetHistorySizeView(unsigned int size)
	{
		m_historysizeview = size;
		m_pos.h = size*m_textheight;
	}
	void GUIDeveloperConsole::WriteLine(std::string str)
	{
		if (m_textinfostr.size() > m_historysize-1)
		{
			m_textinfostr.pop_front();
		}
		else
		{
			if (m_textinfostr.size() >= m_historysizeview)
			{
				if (m_currentline < m_historysize - m_historysizeview) m_currentline++;
			}
		}
		m_textinfostr.push_back(str);

	}
	void GUIDeveloperConsole::Clear()
	{
		m_textinfostr.clear();
	}