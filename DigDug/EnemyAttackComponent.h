#pragma once
#include "BaseComponent.h"

class EnemyAttackComponent final : public dae::BaseComponent
{
public:
	explicit EnemyAttackComponent(dae::GameObject* gameObject);

	~EnemyAttackComponent() override = default;
	EnemyAttackComponent(const EnemyAttackComponent& other) = delete;
	EnemyAttackComponent(EnemyAttackComponent&& other) = delete;
	EnemyAttackComponent& operator=(const EnemyAttackComponent& other) = delete;
	EnemyAttackComponent& operator=(EnemyAttackComponent&& other) = delete;

	void Update() override;
	void FixedUpdate() override;
	void Render() const override;

};
