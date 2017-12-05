#include "GUIObject.hpp"
namespace ThrashEngine {
	GUIObject::GUIObject()
	{

	}
	GUIObject::~GUIObject()
	{

	}
	ResultState GUIObject::Update(int events, double timedelta)
	{
		return ResultState::Success;
		
	}
	ResultState GUIObject::Draw(Graphics* graphics)
	{
		Object::Draw(graphics, 0, 0);
		return ResultState::Success;
	}
	void GUIObject::SetFunction(FunctionPtr ptr)
	{
		m_functionPtr = ptr;
	}
	void GUIObject::SetData(void* dat)
	{
		m_data = dat;
	}
	void GUIObject::SetInput(Input* input)
	{
		m_input = input;
	}
}