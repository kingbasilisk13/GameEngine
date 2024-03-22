#include "KillCommand.h"

#include "HealthComponent.h"

dae::KillCommand::KillCommand(BaseComponent* component)
	:GameComponentCommand(component)
{
}

void dae::KillCommand::Execute()
{
	dynamic_cast<HealthComponent*>(GetGameComponent())->Kill();
}
