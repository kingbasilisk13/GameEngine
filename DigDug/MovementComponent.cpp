#include "MovementComponent.h"

MovementComponent::MovementComponent(dae::GameObject* gameObject, float movementSpeed)
	:BaseComponent(gameObject)
	,m_MovementSpeed(movementSpeed)
{
}

void MovementComponent::Update()
{
	if (m_Direction == glm::vec3{}) return;

	const glm::vec3 deltaMovement = m_MovementSpeed * dae::EngineTime::GetInstance().GetDeltaTime() * glm::normalize(m_Direction);

	GetOwningGameObject()->Translate(deltaMovement);

	m_Direction = {};
}

void MovementComponent::FixedUpdate()
{
}

void MovementComponent::Render() const
{
}

void MovementComponent::SetMovementSpeed(const float movementSpeed)
{
	m_MovementSpeed = movementSpeed;
}

void MovementComponent::SetMovementDirection(const glm::vec3 direction)
{
	m_Direction = direction;
}
