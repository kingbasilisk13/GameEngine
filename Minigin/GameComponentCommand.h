#pragma once
#include <string>

#include "Command.h"

namespace dae
{
	class BaseComponent;

	class GameComponentCommand : public Command
	{
	public:
		explicit GameComponentCommand(BaseComponent* actor, std::string boundSceneName);
		~GameComponentCommand() override;

		GameComponentCommand(const GameComponentCommand& other) = delete;
		GameComponentCommand(GameComponentCommand&& other) = delete;
		GameComponentCommand& operator=(const GameComponentCommand& other) = delete;
		GameComponentCommand& operator=(GameComponentCommand&& other) = delete;

		void Execute() override;

		[[nodiscard]] std::string GetBoundSceneName() const;

	protected:
		[[nodiscard]] BaseComponent* GetGameComponent() const;

	private:
		BaseComponent* m_Component;

		//the scene in which this command get executed.
		std::string m_BoundSceneName;
	};
}

