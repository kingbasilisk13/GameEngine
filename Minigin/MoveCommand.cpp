#include "MoveCommand.h"

#include <glm/geometric.hpp>

#include "GameObject.h"

dae::MoveCommand::MoveCommand(GameObject* actor, const glm::vec3 direction, const float movementSpeed)
	: GameActorCommand(actor)
	,m_Direction(direction)
	,m_MovementSpeed(movementSpeed)
{
	if (m_Direction != glm::vec3{})
	{
		m_Direction = glm::normalize(m_Direction);
	}
}

void dae::MoveCommand::Execute()
{
	if(m_Direction == glm::vec3 {})
	{
		return;
	}
	const auto gameActor = GetGameActor();
	gameActor->SetLocalPosition(gameActor->GetWorldPosition() + (m_MovementSpeed * m_Direction * dae::Time::GetInstance().GetDeltaTime()));
}
