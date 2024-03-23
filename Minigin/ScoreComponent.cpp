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

void dae::ScoreComponent::IncreaseScore(const int points)
{
	m_CurrentScore += points;
	Notify(this, Event::ScoreIncreased);
}

int dae::ScoreComponent::GetScore() const
{
	return m_CurrentScore;
}
