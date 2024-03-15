#pragma once
#include "GameActorCommand.h"
#include "MovementComponent.h"


namespace dae
{
	class MoveCommand : public GameActorCommand
	{
	public:
		MoveCommand(GameObject* actor,const glm::vec3 direction = {0,0,0});

		void Execute() override
		{
			GetGameActor()->GetComponent<MovementComponent>()->AddToMovementDirection(m_Direction);
		}

	private:
		glm::vec3 m_Direction;

	};
}
