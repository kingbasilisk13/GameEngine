#pragma once
#include "Command.h"


class ToggleAudioCommand final : public dae::Command
{
public:
	ToggleAudioCommand();

	void Execute() override;
};

