#include "ToggleAudioCommand.h"

#include "ISoundSystem.h"
#include "ServiceLocator.h"

ToggleAudioCommand::ToggleAudioCommand() = default;

void ToggleAudioCommand::Execute()
{
	dae::ServiceLocator::GetSoundSystem().ToggleAudioMute();
}
