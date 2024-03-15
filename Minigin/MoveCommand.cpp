#include "MoveCommand.h"

dae::MoveCommand::MoveCommand(GameObject* actor, const glm::vec3 direction)
	: GameActorCommand(actor)
	,m_Direction(glm::normalize(direction))
{
}
