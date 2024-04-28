#pragma once
#include <glm/vec3.hpp>
#include "GameComponentCommand.h"


class SetDirectionCommand final : public dae::GameComponentCommand
{
public:
	SetDirectionCommand(dae::BaseComponent* component,const glm::vec3 direction);

	void Execute() override;

private:
	glm::vec3 m_Direction;
};

