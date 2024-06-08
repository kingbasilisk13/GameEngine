#include "SetDirectionCommand.h"

#include <glm/geometric.hpp>
#include <utility>

#include "GameObject.h"
#include "ISoundSystem.h"
#include "GridMovementComponent.h"
#include "ServiceLocator.h"

SetDirectionCommand::SetDirectionCommand(dae::BaseComponent* component, std::string boundSceneName, const glm::vec2 direction)
	: GameComponentCommand(component, std::move(boundSceneName))
	, m_Direction(direction)
{
}

void SetDirectionCommand::Execute()
{
	if(m_Direction == glm::vec2 {})
	{
		return;
	}

	dynamic_cast<GridMovementComponent*>(GetGameComponent())->SetMovementDirection(glm::normalize(m_Direction));
}
