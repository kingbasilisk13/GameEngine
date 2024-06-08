#include "MoveImageCommand.h"

#include <utility>

#include "RenderComponent.h"
#include "SceneManager.h"

MoveImageCommand::MoveImageCommand(dae::BaseComponent* component, std::string boundSceneName, std::vector<glm::vec2> positions)
	:GameComponentCommand(component,boundSceneName)
	,m_Positions(std::move(positions))
{
}

void MoveImageCommand::Execute()
{
	const auto currentSceneName = dae::SceneManager::GetInstance().GetActiveSceneName();

	if(currentSceneName != GetBoundSceneName())
	{
		return;
	}

	const auto renderComponent = dynamic_cast<dae::RenderComponent*>(GetGameComponent());

	const auto renderInfo = renderComponent->GetRenderInfo();

	glm::vec2 currentPosition;

	currentPosition.x = static_cast<float>(renderInfo.destinationX);
	currentPosition.y = static_cast<float>(renderInfo.destinationY);

	for (int i = 0; i < static_cast<int>(m_Positions.size()); ++i)
	{
		if (m_Positions[i] == currentPosition)
		{
			if (const int nextIndex = i + 1; nextIndex >= static_cast<int>(m_Positions.size()))
			{
				renderComponent->ChangeDestinationPosition(static_cast<int>(m_Positions[0].x), static_cast<int>(m_Positions[0].y));
				return;
			}
			else
			{
				renderComponent->ChangeDestinationPosition(static_cast<int>(m_Positions[nextIndex].x), static_cast<int>(m_Positions[nextIndex].y));
				return;
			}
		}
	}
	renderComponent->ChangeDestinationPosition(static_cast<int>(m_Positions[0].x), static_cast<int>(m_Positions[0].y));
}