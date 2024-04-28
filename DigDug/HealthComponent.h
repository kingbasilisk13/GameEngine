#pragma once
#include "BaseComponent.h"
#include "Subject.h"


class HealthComponent final : public dae::BaseComponent
{
public:
	explicit HealthComponent(dae::GameObject* gameObject, const int numberOfLives);

	~HealthComponent() override = default;
	HealthComponent(const HealthComponent& other) = delete;
	HealthComponent(HealthComponent&& other) = delete;
	HealthComponent& operator=(const HealthComponent& other) = delete;
	HealthComponent& operator=(HealthComponent&& other) = delete;

	void Update() override;
	void FixedUpdate() override;
	void Render() const override;

	void Kill();

	[[nodiscard]] int GetRemainingLives() const;

	void SubscribeToHealthChangedEvent(dae::IObserver* observer) const;

private:
	int m_Lives;
	std::unique_ptr<dae::Subject> m_HealthChangedEvent;
};

