#include "SetDirectionCommand.h"

#include <glm/geometric.hpp>

#include "GameObject.h"
#include "ISoundSystem.h"
#include "MovementComponent.h"
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

	dae::ServiceLocator::GetSoundSystem().PlayMusic(24,200,-1);

	dynamic_cast<MovementComponent*>(GetGameComponent())->SetMovementDirection(glm::normalize(m_Direction));
}
