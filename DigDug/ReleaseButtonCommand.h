#pragma once
#include "GameComponentCommand.h"

class ReleaseButtonCommand final : public dae::Command
{
public:
	ReleaseButtonCommand()=default;

	void Execute() override;

};
