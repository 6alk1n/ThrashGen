#pragma once
/*******
//Camera.hpp camera class.
Contains position, projections(view) and scale
********/
#include "Core.hpp"
namespace ThrashEngine {
	class Camera
	{
	public:
		Camera();
		~Camera();

		Vector GetPos();
		Vector GetView();
		double GetScale();
		void SetPos(Vector);
		void SetView(Vector);
		void Move(Vector);
		void SetScale(double);
		void Center(Vector);

	protected:
		Vector m_pos;
		Vector m_view;
		double m_scale;
	};
}