#include "MovementComponent.h"

dae::MovementComponent::MovementComponent(GameObject* gameObject, const float movementSpeed)
	:BaseComponent(gameObject)
	,m_MovementSpeed(movementSpeed)
{
}

void dae::MovementComponent::Update()
{
	if (m_Direction == glm::vec3{}) return;

	const glm::vec3 deltaMovement = m_MovementSpeed * dae::Time::GetInstance().GetDeltaTime() * glm::normalize(m_Direction);

	GetOwningGameObject()->Translate(deltaMovement);

	m_Direction = {};
}

void dae::MovementComponent::FixedUpdate()
{
}

void dae::MovementComponent::Render() const
{
}

void dae::MovementComponent::SetMovementSpeed(const float movementSpeed)
{
	m_MovementSpeed = movementSpeed;
}

void dae::MovementComponent::AddToMovementDirection(const glm::vec3 direction)
{
	m_Direction.x += direction.x;
	m_Direction.y += direction.y;
}
