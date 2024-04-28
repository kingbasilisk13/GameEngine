#pragma once
#include "GameComponentCommand.h"


class ScoreCommand final : public dae::GameComponentCommand
{
public:
	ScoreCommand(dae::BaseComponent* component,const int amountOfPoints);

	void Execute() override;

private:
	int m_AmountOfPoints{};
};
