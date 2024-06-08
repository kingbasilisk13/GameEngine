#pragma once
#include <string>

#include "GameComponentCommand.h"

class AcceptSelectedGameModeCommand final : public dae::GameComponentCommand
{
public:
	AcceptSelectedGameModeCommand(dae::BaseComponent* component, std::string boundSceneName);

	void Execute() override;
};
