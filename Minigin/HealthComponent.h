#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
	class HealthComponent final : public BaseComponent, public Subject
	{
	public:
		explicit HealthComponent(GameObject* gameObject, const int numberOfLives);

		~HealthComponent() override = default;
		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void Kill();

		int GetRemainingLives() const;

	private:
		int m_Lives{};
	};
}
