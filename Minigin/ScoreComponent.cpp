#include "ScoreComponent.h"

dae::ScoreComponent::ScoreComponent(GameObject* gameObject)
:BaseComponent(gameObject)
{
}

void dae::ScoreComponent::Update()
{
}

void dae::ScoreComponent::FixedUpdate()
{
}

void dae::ScoreComponent::Render() const
{
}


//todo: dit is verkeerd. het is de bedoeling dat de notify gebeurt op een event in de game.
//een event gebeurt (enemie sterf, item wordt opgeraapt, speler sterf) en de score bijhouder beslist dan zelf hoeveel punten dat waard is.
void dae::ScoreComponent::IncreaseScore(const int points)
{
	m_CurrentScore += points;
	Notify(this, Event::ScoreIncreased);
}

int dae::ScoreComponent::GetScore() const
{
	return m_CurrentScore;
}
