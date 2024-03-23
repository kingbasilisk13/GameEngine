#include "ScoreCommand.h"

#include "ScoreComponent.h"

dae::ScoreCommand::ScoreCommand(BaseComponent* component, const int amountOfPoints)
	:GameComponentCommand(component)
	,m_AmountOfPoints(amountOfPoints)
{
}

void dae::ScoreCommand::Execute()
{
	dynamic_cast<ScoreComponent*>(GetGameComponent())->IncreaseScore(m_AmountOfPoints);
}
