#include "SelectGameModeCommand.h"

#include <utility>

#include "GameModeSelectorComponent.h"
#include "SceneManager.h"

SelectGameModeCommand::SelectGameModeCommand(dae::BaseComponent* component, std::string boundSceneName, std::vector<GameMode> gameModeOrder)
	:GameComponentCommand(component, std::move(boundSceneName))
	, m_GameModes(std::move(gameModeOrder))
{
}

void SelectGameModeCommand::Execute()
{
	const auto currentSceneName = dae::SceneManager::GetInstance().GetActiveSceneName();

	if (currentSceneName != GetBoundSceneName())
	{
		return;
	}

	const auto gameModeSelectorComponent = dynamic_cast<GameModeSelectorComponent*>(GetGameComponent());
	const auto currentGameMode = gameModeSelectorComponent->GetCurrentGameMode();

	for (int i = 0; i < static_cast<int>(m_GameModes.size()); ++i)
	{
		if (m_GameModes[i] == currentGameMode)
		{
			if (const int nextIndex = i + 1; nextIndex >= static_cast<int>(m_GameModes.size()))
			{
				gameModeSelectorComponent->SetSelectedGameMode(m_GameModes[0]);
				return;
			}
			else
			{
				gameModeSelectorComponent->SetSelectedGameMode(m_GameModes[nextIndex]);
				return;
			}
		}
	}
}
