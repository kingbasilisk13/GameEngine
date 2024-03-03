#include "RotatorComponent.h"

#include <SDL_stdinc.h>

dae::RotatorComponent::RotatorComponent(GameObject* gameObject, const float radius, const float maxTime, const bool clockwise)
	: BaseComponent(gameObject)
	,m_Clockwise(clockwise)
	,m_Radius(radius)
	,m_TotalTime(0.f)
	,m_MaxTime(maxTime)
	,m_Owner(nullptr)
{
	m_Owner = GetOwningGameObject();
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
		if (m_TotalTime >= m_MaxTime)
		{
			m_TotalTime = 0;
		}
	}
	else
	{
		m_TotalTime -= time;
		if (m_TotalTime <= 0)
		{
			m_TotalTime = m_MaxTime;
		}
	}

	const float speed = (m_TotalTime / m_MaxTime) * m_Pi2;

	glm::vec3 position{};

	position.x = cos(speed) * m_Radius;
	position.y = sin(speed) * m_Radius;

	m_Owner->SetLocalPosition(position);
}
