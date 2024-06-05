#pragma once
#include <string>

#include "Command.h"
#include <vector>

class SwitchLevelCommand final : public dae::Command
{
public:
	SwitchLevelCommand(std::vector<std::string> vectorOfLevels);

	void Execute() override;

private:
	std::vector<std::string> m_VectorOfLevels;
};
