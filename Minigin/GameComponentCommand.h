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

		GameComponentCommand(const GameComponentCommand& other) = delete;
		GameComponentCommand(GameComponentCommand&& other) = delete;
		GameComponentCommand& operator=(const GameComponentCommand& other) = delete;
		GameComponentCommand& operator=(GameComponentCommand&& other) = delete;

	protected:
		[[nodiscard]] BaseComponent* GetGameComponent() const;

	public:
		void Execute() override;

	private:
		BaseComponent* m_Component;
	};
}

