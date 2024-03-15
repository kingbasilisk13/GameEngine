#pragma once
#include "Command.h"

namespace dae
{
	class GameObject;

	class GameActorCommand : public Command
	{
	public:
		GameActorCommand(GameObject* actor);
		virtual ~GameActorCommand();

	protected:
		[[nodiscard]] GameObject* GetGameActor() const { return m_Actor; }

	private:
		GameObject* m_Actor;
	};
}

