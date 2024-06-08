#pragma once
#include <string>

#include "Command.h"
#include <vector>

class SkipLevelCommand final : public dae::Command
{
public:
	SkipLevelCommand(std::vector<std::string> vectorOfLevels);

	void Execute() override;

private:
	std::vector<std::string> m_VectorOfLevels;
};
