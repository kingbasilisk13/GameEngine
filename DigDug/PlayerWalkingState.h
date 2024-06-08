#pragma once

#include "IObserver.h"
#include "IPlayerStateBase.h"
#include "RenderComponent.h"

class PlayerWalkingState final : public IPlayerStateBase, public dae::IObserver
{
public:

	PlayerWalkingState(PlayerInput previousDirection, dae::FlipImage imageFlip);
	~PlayerWalkingState() override;

	void HandleInput(PlayerInput input) override;

	IState* Update(dae::GameObject* owner) override;

	void OnEnter(dae::GameObject* owner) override;

	void OnExit() override;

	void OnGlobalNotify(const std::string event) override;

	void OnNotify(dae::Subject* component, dae::Event event) override;
	void AddSubject(dae::Subject* subject) override;
	void InformAllSubjects(std::vector<dae::Subject*> subjects) override;

	PlayerWalkingState(const PlayerWalkingState& other) = delete;
	PlayerWalkingState(PlayerWalkingState&& other) = delete;
	PlayerWalkingState& operator=(const PlayerWalkingState& other) = delete;
	PlayerWalkingState& operator=(PlayerWalkingState&& other) = delete;

private:
	bool m_PlayerIsIdle = false;

	bool m_PlayerHasDied = false;

	PlayerInput m_Direction = PlayerInput::right;
	PlayerInput m_PreviousDirection = PlayerInput::right;

	dae::FlipImage m_Flip;

	void CalculateDirection(dae::GameObject* owner);

	void InvertImageFlip();

};
