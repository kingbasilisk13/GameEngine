#include "ScoreCommand.h"

#include <utility>

#include "ScoreComponent.h"

ScoreCommand::ScoreCommand(dae::BaseComponent* component, std::string boundSceneName, const int amountOfPoints)
	:GameComponentCommand(component, std::move(boundSceneName))
	,m_AmountOfPoints(amountOfPoints)
{
}

void ScoreCommand::Execute()
{
	dynamic_cast<ScoreComponent*>(GetGameComponent())->IncreaseScore(m_AmountOfPoints);
}
