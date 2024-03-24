#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
	class ScoreComponent final : public BaseComponent, public Subject
	{
	public:
		explicit ScoreComponent(GameObject* gameObject);

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

	private:
		int m_CurrentScore{ 0 };
	};
}