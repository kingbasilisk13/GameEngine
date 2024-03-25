#pragma once
#include <glm/vec3.hpp>
#include "GameComponentCommand.h"

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
