#include "SetDirectionCommand.h"

#include <glm/geometric.hpp>

#include "GameObject.h"
#include "ISoundSystem.h"
#include "GridMovementComponent.h"
#include "ServiceLocator.h"

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

	dae::ServiceLocator::GetSoundSystem().PlayMusic(24,50,-1);

	dynamic_cast<GridMovementComponent*>(GetGameComponent())->SetMovementDirection(glm::normalize(m_Direction));
}
