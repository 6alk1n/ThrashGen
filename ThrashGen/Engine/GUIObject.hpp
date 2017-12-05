#pragma once
#include "Object.hpp"
#include "Input.hpp"
namespace ThrashEngine
{
	const int EventMouseIn = 1;
	const int EventMouseOut = 1 << 1;
	const int EventMouseClickLeft = 1 << 2;
	const int EventMouseOnClickLeft = 1 << 3;
	
	typedef  void *(*FunctionPtr)(void*);

	class GUIObject : public Object
	{
	public:
		GUIObject();
		virtual ~GUIObject();
		virtual ResultState Update(int, double);
		virtual ResultState Draw(Graphics*);
		void SetFunction(FunctionPtr);
		void SetData(void*);
		void SetInput(Input*);
	protected:
		FunctionPtr m_functionPtr;
		void* m_data;
		Input* m_input;
	};

	


}