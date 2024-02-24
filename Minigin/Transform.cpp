#include "Transform.h"


dae::Transform::Transform(float x, float y, float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;

	m_Rotation.x = 0.f;
	m_Rotation.y = 0.f;
	m_Rotation.z = 0.f;

	m_Scale.x = 1.f;
	m_Scale.y = 1.f;
	m_Scale.z = 1.f;
}

void dae::Transform::Update()
{
}

void dae::Transform::Render(float posX, float posY) const
{
	posX;
	posY;
}

void dae::Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}
