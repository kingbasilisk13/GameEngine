#include "ScoreComponent.h"

dae::ScoreComponent::ScoreComponent(GameObject* gameObject)
:BaseComponent(gameObject)
{
	m_ScoreChangedEvent = std::make_unique<dae::Subject>(this);
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
	m_ScoreChangedEvent->Notify(Event::ScoreIncreased);
}

int dae::ScoreComponent::GetScore() const
{
	return m_CurrentScore;
}

void dae::ScoreComponent::SubscribeToScoreChangedEvent(IObserver* observer) const
{
	m_ScoreChangedEvent->AddObserver(observer);
}
