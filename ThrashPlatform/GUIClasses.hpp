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
