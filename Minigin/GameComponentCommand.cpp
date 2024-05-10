#include "GameComponentCommand.h"

#include "BaseComponent.h"

dae::GameComponentCommand::GameComponentCommand(BaseComponent* actor)
	:Command()
	, m_Component(actor)
{
}

dae::GameComponentCommand::~GameComponentCommand() = default;

dae::BaseComponent* dae::GameComponentCommand::GetGameComponent() const
{
	return m_Component;
}


void dae::GameComponentCommand::Execute()
{
}
