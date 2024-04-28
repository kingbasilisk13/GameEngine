#include "KillCommand.h"

#include "HealthComponent.h"

KillCommand::KillCommand(dae::BaseComponent* component)
	:GameComponentCommand(component)
{
}

void KillCommand::Execute()
{
	dynamic_cast<HealthComponent*>(GetGameComponent())->Kill();
}
