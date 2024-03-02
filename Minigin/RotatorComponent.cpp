#include "RotatorComponent.h"

#include <SDL_stdinc.h>

#include "Time.h"

dae::RotatorComponent::RotatorComponent(GameObject* gameObject, const float radius, const float maxTime, const bool clockwise)
	: BaseComponent(gameObject)
	,m_Clockwise(clockwise)
	,m_Radius(radius)
	,m_TotalTime(0.f)
	,m_MaxTime(maxTime)
	,m_Center({})
	,m_Owner(GetOwningGameObject())
	,m_Pi2(2.f * static_cast<float>(M_PI))
{

}

void dae::RotatorComponent::Update()
{
	CalculateRotation(dae::Time::GetInstance().GetDeltaTime());
}

void dae::RotatorComponent::FixedUpdate(const float fixedTimeStep)
{
	CalculateRotation(fixedTimeStep);
}

void dae::RotatorComponent::Render(float , float ) const
{
}

void dae::RotatorComponent::CalculateRotation(const float time)
{
	if (m_Clockwise)
	{
		m_TotalTime += time;
	}
	else
	{
		m_TotalTime -= time;
	}

	if (m_Clockwise)
	{
		if (m_TotalTime >= m_MaxTime)
		{
			m_TotalTime = 0;
		}
	}
	else
	{
		if (m_TotalTime <= 0)
		{
			m_TotalTime = m_MaxTime;
		}
	}

	const float speed = (m_TotalTime / m_MaxTime) * m_Pi2;

	m_Center.x += sin(speed) * m_Radius;
	m_Center.y += cos(speed) * m_Radius;

	m_Owner.SetLocalPosition(m_Center);
}
