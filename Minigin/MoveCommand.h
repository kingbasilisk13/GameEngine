#pragma once
#include <glm/vec3.hpp>

#include "GameActorCommand.h"

//todo: do not create a component that does what the command is suposed to do.

namespace dae
{
	class MoveCommand : public GameActorCommand
	{
	public:
		MoveCommand(GameObject* actor,const glm::vec3 direction, const float movementSpeed);

		void Execute() override;

	private:
		glm::vec3 m_Direction;
		float m_MovementSpeed;
	};
}
