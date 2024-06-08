#include "RegisterInputCommand.h"

#include "AnimationComponent.h"
#include "IPlayerStateBase.h"
#include "StateComponent.h"

RegisterInputCommand::RegisterInputCommand(dae::BaseComponent* component, std::string boundSceneName, const PlayerInput input)
	: GameComponentCommand(component,boundSceneName)
	,m_Input(input)
{
}

void RegisterInputCommand::Execute()
{
	auto state = dynamic_cast<dae::StateComponent*>(GetGameComponent())->GetCurrentState();

	dynamic_cast<IPlayerStateBase*>(state)->HandleInput(m_Input);

}
