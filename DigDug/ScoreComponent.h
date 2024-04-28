#pragma once
#include "BaseComponent.h"
#include "Subject.h"

class ScoreComponent final : public dae::BaseComponent
{
public:
	explicit ScoreComponent(dae::GameObject* gameObject);

	~ScoreComponent() override = default;
	ScoreComponent(const ScoreComponent& other) = delete;
	ScoreComponent(ScoreComponent&& other) = delete;
	ScoreComponent& operator=(const ScoreComponent& other) = delete;
	ScoreComponent& operator=(ScoreComponent&& other) = delete;

	void Update() override;
	void FixedUpdate() override;
	void Render() const override;

	void IncreaseScore(int points);

	[[nodiscard]] int GetScore() const;

	void SubscribeToScoreChangedEvent(dae::IObserver* observer) const;

private:
	int m_CurrentScore{ 0 };
	std::unique_ptr<dae::Subject> m_ScoreChangedEvent;
};