#pragma once
#include "Command.h"


namespace dae
{
	class BaseComponent;
	class GameComponentCommand : public Command
	{
	public:
		explicit GameComponentCommand(BaseComponent* actor);
		~GameComponentCommand() override;

	protected:
		[[nodiscard]] BaseComponent* GetGameComponent() const;

	public:
		void Execute() override;

	private:
		BaseComponent* m_Component;
	};
}

