#include "Camera.hpp"

namespace ThrashEngine {

	Camera::Camera(){}
	Camera::~Camera(){}

	Vector Camera::GetPos() { return m_pos; }
	Vector Camera::GetView() { return m_view; }
	double Camera::GetScale() { return m_scale; }
	void Camera::SetPos(Vector pos) { m_pos = pos; }
	void Camera::SetView(Vector pos) { m_view = pos; }
	void Camera::Move(Vector off) { m_pos += off; }
	void Camera::SetScale(double sc) { m_scale = sc; }
	void Camera::Center(Vector center) 
	{
		m_pos.x = center.x - m_view.x / 2; 
		m_pos.y = center.y - m_view.y / 2;	
	}
}