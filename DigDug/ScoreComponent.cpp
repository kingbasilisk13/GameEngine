#include "ScoreComponent.h"

ScoreComponent::ScoreComponent(dae::GameObject* gameObject)
:BaseComponent(gameObject)
{
	m_ScoreChangedEvent = std::make_unique<dae::Subject>(this);
}

void ScoreComponent::Update()
{
}

void ScoreComponent::FixedUpdate()
{
}

void ScoreComponent::Render() const
{
}


void ScoreComponent::IncreaseScore(const int points)
{
	m_CurrentScore += points;
	m_ScoreChangedEvent->Notify(dae::Event::ScoreIncreased);
}

int ScoreComponent::GetScore() const
{
	return m_CurrentScore;
}

void ScoreComponent::SubscribeToScoreChangedEvent(dae::IObserver* observer) const
{
	m_ScoreChangedEvent->AddObserver(observer);
}
