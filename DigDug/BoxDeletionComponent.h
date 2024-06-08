#pragma once
#include "BaseComponent.h"

enum class GameMode;

//when the player overlaps with this component it will delete the box component and then itself.
class BoxDeletionComponent final : public dae::BaseComponent
{
public:
	explicit BoxDeletionComponent(dae::GameObject* gameObject, GameMode gameMode);

	~BoxDeletionComponent() override = default;
	BoxDeletionComponent(const BoxDeletionComponent& other) = delete;
	BoxDeletionComponent(BoxDeletionComponent&& other) = delete;
	BoxDeletionComponent& operator=(const BoxDeletionComponent& other) = delete;
	BoxDeletionComponent& operator=(BoxDeletionComponent&& other) = delete;

	void Update() override;
	void FixedUpdate() override;
	void Render() const override;

private:
	dae::GameObject* m_Player1 = nullptr;
	dae::GameObject* m_Player2 = nullptr;

	GameMode m_GameMode;


	void CheckIfNeedToDeleteCell(dae::GameObject* player);


};
