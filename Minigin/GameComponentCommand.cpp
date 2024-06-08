#include "GameComponentCommand.h"

#include "BaseComponent.h"

dae::GameComponentCommand::GameComponentCommand(BaseComponent* actor, std::string boundSceneName)
	:Command()
	, m_Component(actor)
	,m_BoundSceneName(boundSceneName)
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

std::string dae::GameComponentCommand::GetBoundSceneName() const
{
	return m_BoundSceneName;
}
