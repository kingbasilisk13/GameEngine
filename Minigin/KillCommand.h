#pragma once
#include "GameComponentCommand.h"

namespace dae
{
	class KillCommand final : public GameComponentCommand
	{
	public:
		KillCommand(BaseComponent* component);

		void Execute() override;

	private:
		
	};
}
