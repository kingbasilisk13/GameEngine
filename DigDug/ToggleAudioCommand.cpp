#include "ToggleAudioCommand.h"

#include "ISoundSystem.h"
#include "ServiceLocator.h"

ToggleAudioCommand::ToggleAudioCommand()
{
}

void ToggleAudioCommand::Execute()
{
	dae::ServiceLocator::GetSoundSystem().ToggleAudioMute();
}
