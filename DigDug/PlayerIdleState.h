#pragma once
#include "IObserver.h"
#include "IPlayerStateBase.h"

namespace dae
{
	enum class FlipImage;
}

class PlayerIdleState final : public IPlayerStateBase, public dae::IObserver
{
public:
	explicit PlayerIdleState(PlayerInput previousDirection, dae::FlipImage imageFlip);
	~PlayerIdleState() override;

	void HandleInput(PlayerInput input) override;

	IState* Update(dae::GameObject* owner) override;

	void OnEnter(dae::GameObject* owner) override;

	void OnExit() override;

	void OnGlobalNotify(const std::string event) override;

	PlayerIdleState(const PlayerIdleState& other) = delete;
	PlayerIdleState(PlayerIdleState&& other) = delete;
	PlayerIdleState& operator=(const PlayerIdleState& other) = delete;
	PlayerIdleState& operator=(PlayerIdleState&& other) = delete;

	void OnNotify(dae::Subject* component, dae::Event event) override;
	void AddSubject(dae::Subject* subject) override;
	void InformAllSubjects(std::vector<dae::Subject*> subjects) override;

private:
	bool m_PressedInput = false;

	bool m_PlayerHasDied = false;

	PlayerInput m_PreviousDirection;
	dae::FlipImage m_Flip;
};
