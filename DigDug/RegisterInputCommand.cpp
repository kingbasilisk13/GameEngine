#include "RegisterInputCommand.h"

#include "AnimationComponent.h"
#include "IPlayerStateBase.h"
#include "StateComponent.h"

RegisterInputCommand::RegisterInputCommand(dae::BaseComponent* component, const PlayerInput input)
	: GameComponentCommand(component)
	,m_Input(input)
{
}

void RegisterInputCommand::Execute()
{
	auto state = dynamic_cast<dae::StateComponent*>(GetGameComponent())->GetCurrentState();

	dynamic_cast<IPlayerStateBase*>(state)->HandleInput(m_Input);

}
