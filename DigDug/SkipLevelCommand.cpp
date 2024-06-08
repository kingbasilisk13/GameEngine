#include "SkipLevelCommand.h"

#include "SceneManager.h"

SkipLevelCommand::SkipLevelCommand(std::vector<std::string> vectorOfLevels)
	:m_VectorOfLevels(vectorOfLevels)
{
}

void SkipLevelCommand::Execute()
{
	const auto currentSceneName = dae::SceneManager::GetInstance().GetActiveSceneName();

	for(int i = 0; i < static_cast<int>(m_VectorOfLevels.size()); ++i)
	{
		if(m_VectorOfLevels[i] == currentSceneName)
		{
			if(i + 1 >= static_cast<int>(m_VectorOfLevels.size()))
			{
				//todo: replace this with a command that returns user to main menu.
				dae::SceneManager::GetInstance().OpenSceneByName("MainMenu");
			}
			else
			{
				dae::SceneManager::GetInstance().OpenSceneByName(m_VectorOfLevels[i+1]);
			}
		}
	}
}

