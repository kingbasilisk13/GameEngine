#include "RotatorComponent.h"

#include <SDL_stdinc.h>

dae::RotatorComponent::RotatorComponent(GameObject* gameObject, const float radius, const float speed, const bool clockwise)
	: BaseComponent(gameObject)
	, m_Direction{-1}
	, m_Radius(radius)
	, m_Speed(speed)
{
	if (clockwise) m_Direction = 1;
}

void dae::RotatorComponent::Update()
{
	CalculateRotation(dae::Time::GetInstance().GetDeltaTime());
}

void dae::RotatorComponent::FixedUpdate()
{
}

void dae::RotatorComponent::Render() const
{
}

void dae::RotatorComponent::CalculateRotation(const float time)
{
	constexpr float twoPi = 2.f * static_cast<float>(M_PI);

	m_Angle += m_Speed * time;

	if(m_Angle > twoPi)
	{
		m_Angle -= twoPi;
	}

	GetOwningGameObject()->SetLocalPosition(
	{
		cos(m_Angle * m_Direction) * m_Radius,
		sin(m_Angle * m_Direction) * m_Radius,
		0
	});
}
