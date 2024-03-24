#pragma once
#include <glm/vec3.hpp>

#include "GameComponentCommand.h"

//todo: do not create a component that does what the command is supposed to do.
//todo: ask again to explain how to use command correctly.

namespace dae
{
	class SetDirectionCommand final : public GameComponentCommand
	{
	public:
		SetDirectionCommand(BaseComponent* component,const glm::vec3 direction);

		void Execute() override;

	private:
		glm::vec3 m_Direction;
	};
}