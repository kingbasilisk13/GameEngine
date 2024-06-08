#pragma once
#include "GameComponentCommand.h"

enum class PlayerInput;

class RegisterInputCommand final : public dae::GameComponentCommand
{
public:
	RegisterInputCommand(dae::BaseComponent* component, std::string boundSceneName, const PlayerInput input);

	void Execute() override;

private:
	PlayerInput m_Input;
};
