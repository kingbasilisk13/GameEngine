#include "MovementComponent.h"

#include "Renderer.h"

MovementComponent::MovementComponent(dae::GameObject* gameObject, float movementSpeed)
	:BaseComponent(gameObject)
	,m_MovementSpeed(movementSpeed)
{
	dae::Renderer::GetInstance().GetWindowSize(&m_WindowWidth, &m_WindowHeight);
}

void MovementComponent::Update()
{
	if (m_Direction == glm::vec3{}) return;

	const glm::vec3 deltaMovement = m_MovementSpeed * dae::EngineTime::GetInstance().GetDeltaTime() * glm::normalize(m_Direction);

	const auto position = GetOwningGameObject()->GetWorldPosition();

	if(position.x + deltaMovement.x > m_WindowWidth || position.x + deltaMovement.x < 0)
	{
		return;
	}

	if (position.y + deltaMovement.y > m_WindowHeight || position.y + deltaMovement.y < 0)
	{
		return;
	}

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
