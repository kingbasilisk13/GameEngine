#pragma once
#include "GameComponentCommand.h"

namespace dae
{
	class ScoreCommand final : public GameComponentCommand
	{
	public:
		ScoreCommand(BaseComponent* component,const int amountOfPoints);

		void Execute() override;

	private:
		int m_AmountOfPoints{};
	};
}