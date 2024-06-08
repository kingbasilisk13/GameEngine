#include "AcceptSelectedGameModeCommand.h"

#include <utility>

#include "GameModeSelectorComponent.h"
#include "SceneManager.h"

AcceptSelectedGameModeCommand::AcceptSelectedGameModeCommand(dae::BaseComponent* component, std::string boundSceneName)
	:GameComponentCommand(component,boundSceneName)
{
}

void AcceptSelectedGameModeCommand::Execute()
{
	if (const auto currentSceneName = dae::SceneManager::GetInstance().GetActiveSceneName(); currentSceneName != GetBoundSceneName())
	{
		return;
	}

	dynamic_cast<GameModeSelectorComponent*>(GetGameComponent())->LoadLevelsBasedOnGameMode();

}
