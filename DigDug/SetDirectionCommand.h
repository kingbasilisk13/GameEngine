#pragma once
#include <glm/vec2.hpp>
#include "GameComponentCommand.h"


class SetDirectionCommand final : public dae::GameComponentCommand
{
public:
	SetDirectionCommand(dae::BaseComponent* component,std::string boundSceneName, const glm::vec2 direction);

	void Execute() override;

private:
	glm::vec2 m_Direction;
};

