#pragma once
#include <string>
#include <vector>

#include "GameComponentCommand.h"

enum class GameMode;

class SelectGameModeCommand final : public dae::GameComponentCommand
{
public:
	SelectGameModeCommand(dae::BaseComponent* component, std::string boundSceneName, std::vector<GameMode> gameModeOrder);

	void Execute() override;

private:
	//game modes
	std::vector<GameMode> m_GameModes;
};
