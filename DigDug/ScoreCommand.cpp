#include "ScoreCommand.h"

#include "ScoreComponent.h"

ScoreCommand::ScoreCommand(dae::BaseComponent* component, const int amountOfPoints)
	:GameComponentCommand(component)
	,m_AmountOfPoints(amountOfPoints)
{
}

void ScoreCommand::Execute()
{
	dynamic_cast<ScoreComponent*>(GetGameComponent())->IncreaseScore(m_AmountOfPoints);
}
