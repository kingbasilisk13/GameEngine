#pragma once
#include "BaseComponent.h"

enum class GameMode
{
	singlePlayer,
	coOp,
	vS
};
class GameModeSelectorComponent final : public dae::BaseComponent
{
public:
	explicit GameModeSelectorComponent(dae::GameObject* gameObject, std::vector<glm::vec2> positions);

	~GameModeSelectorComponent() override = default;
	GameModeSelectorComponent(const GameModeSelectorComponent& other) = delete;
	GameModeSelectorComponent(GameModeSelectorComponent&& other) = delete;
	GameModeSelectorComponent& operator=(const GameModeSelectorComponent& other) = delete;
	GameModeSelectorComponent& operator=(GameModeSelectorComponent&& other) = delete;

	void Update() override;
	void FixedUpdate() override;
	void Render() const override;

private:
	GameMode m_GameMode = GameMode::singlePlayer;
};
