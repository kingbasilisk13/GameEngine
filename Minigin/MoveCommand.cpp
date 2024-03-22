#include "MoveCommand.h"

#include <glm/geometric.hpp>

#include "GameObject.h"
#include "MovementComponent.h"

dae::MoveCommand::MoveCommand(BaseComponent* component, const glm::vec3 direction, const float movementSpeed)
	: GameComponentCommand(component)
	, m_Direction(direction)
	, m_MovementSpeed(movementSpeed)
{
}

void dae::MoveCommand::Execute()
{
	if(m_Direction == glm::vec3 {})
	{
		return;
	}
	dynamic_cast<MovementComponent*>(GetGameComponent())->AddToMovementDirection(m_Direction);
}
