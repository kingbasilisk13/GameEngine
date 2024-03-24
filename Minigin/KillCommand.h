#pragma once
#include "GameComponentCommand.h"

namespace dae
{
	class KillCommand final : public GameComponentCommand
	{
	public:
		explicit KillCommand(BaseComponent* component);

		void Execute() override;
		
	};
}
