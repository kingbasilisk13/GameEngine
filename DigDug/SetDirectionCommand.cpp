#include "SetDirectionCommand.h"

#include <glm/geometric.hpp>

#include "GameObject.h"
#include "MovementComponent.h"

SetDirectionCommand::SetDirectionCommand(dae::BaseComponent* component, const glm::vec3 direction)
	: GameComponentCommand(component)
	, m_Direction(direction)
{
}

void SetDirectionCommand::Execute()
{
	if(m_Direction == glm::vec3 {})
	{
		return;
	}
	dynamic_cast<MovementComponent*>(GetGameComponent())->AddToMovementDirection(glm::normalize(m_Direction));
}
