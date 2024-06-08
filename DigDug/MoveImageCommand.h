#pragma once
#include <string>
#include <glm/vec2.hpp>

#include "GameComponentCommand.h"
#include <vector>

namespace dae
{
	class RenderComponent;
}

//to reverse the move command make the command again but use the reverse order of the array
class MoveImageCommand final : public dae::GameComponentCommand
{
public:
	MoveImageCommand(dae::BaseComponent* component, std::string activeScene, std::vector<glm::vec2> positions );

	void Execute() override;

private:
	//a string that keeps track of wich level the command should be active in.
	std::string m_ActiveScene;

	//positions of the image.
	std::vector<glm::vec2> m_Positions;
};
