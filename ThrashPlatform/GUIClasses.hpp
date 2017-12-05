#pragma once
#include <Engine\GUIObject.hpp>
#include <Engine\Font.hpp>

	class GUIButton :public ThrashEngine::GUIObject
	{
	public:
		GUIButton();
		virtual ~GUIButton();
		virtual ThrashEngine::ResultState Update(int, double);
		virtual ThrashEngine::ResultState Draw(ThrashEngine::Graphics*);
		void SetBorderColor(SDL_Color);
	protected:
		SDL_Color borderColor;
		bool mouseon;
	};

	class GUISpinButton : public ThrashEngine::GUIObject
	{
	public:
		GUISpinButton();
		virtual ~GUISpinButton();
		virtual ThrashEngine::ResultState Update(int, double);
		virtual ThrashEngine::ResultState Draw(ThrashEngine::Graphics*);
		double GetValue();
		void SetValue(double);
		void SetMin(double);
		void SetMax(double);
		void SetStep(double);
		void SetTextSizeRelative(double);
		void SetFont(ThrashEngine::Font*);
		void SetText(std::string);
	protected:
		double value;
		double min;
		double max;
		double step;
		double textsizerel;
		int mouseonbutton;
		ThrashEngine::FontField text;
		ThrashEngine::FontField title;
		std::string titletext;
		double timing;
	};

	class GUIInputLabel :public ThrashEngine::GUIObject
	{
	public:
		GUIInputLabel();
		~GUIInputLabel();
		virtual ThrashEngine::ResultState Update(int, double);
		virtual ThrashEngine::ResultState Draw(ThrashEngine::Graphics*);
		virtual ThrashEngine::ResultState UpdateInput(int);
		std::string GetInputLabel();
		void SetFont(ThrashEngine::Font*);
		void SetActiveLabel(bool);
		void SetBorderColor(SDL_Color);
		void SetBackgroundColor(SDL_Color);
		void SetTextSize(unsigned int, unsigned int);
		ThrashEngine::Text m_text;
		void SetResendObj(GUIObject*);
	protected:
		GUIObject* m_resendInputObj;
		std::string m_str;
		std::string m_result;
		bool m_activelabel;
		SDL_Color m_bordercolor, m_backcolor;
	};

	class GUIDeveloperConsole :public ThrashEngine::GUIObject
	{
	public:
		GUIDeveloperConsole();
		~GUIDeveloperConsole();
		virtual ThrashEngine::ResultState Update(int, double);
		virtual ThrashEngine::ResultState Draw(ThrashEngine::Graphics*);
		virtual ThrashEngine::ResultState UpdateInput(int);

		void SetFont(ThrashEngine::Font*);
		void SetActiveLabel(bool);
		bool GetActiveLabel();
		void SetBorderColor(SDL_Color);
		void SetBackgroundColor(SDL_Color);	
		void SetBorderColorInfo(SDL_Color);
		void SetBackgroundColorInfo(SDL_Color);
		void SetTextSize(unsigned int, unsigned int);
		void SetHistorySize(unsigned int);
		void SetHistorySizeView(unsigned int);
		void WriteLine(std::string);
		GUIInputLabel m_inputlabel;
		void Clear();
	protected:
		ThrashEngine::Text m_textinfo;
		std::list<std::string> m_textinfostr;
		bool m_activelabel;
		SDL_Color m_bordercolor, m_backcolor;
		unsigned int m_historysize;
		unsigned int m_historysizeview;
		unsigned int m_currentline;
		unsigned int m_textheight;
	};
