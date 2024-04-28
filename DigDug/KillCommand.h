#pragma once
#include "GameComponentCommand.h"


class KillCommand final : public dae::GameComponentCommand
{
public:
	KillCommand(dae::BaseComponent* component);

	void Execute() override;

};

