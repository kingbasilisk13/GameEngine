#include "GameActorCommand.h"

dae::GameActorCommand::GameActorCommand(GameObject* actor)
	:Command()
	,m_Actor(actor)
{
}

dae::GameActorCommand::~GameActorCommand() = default;
