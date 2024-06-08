#pragma once
#include "BaseComponent.h"
#include "IObserver.h"

class ResetPositionComponent final : public dae::BaseComponent, public dae::IObserver
{
public:
	explicit ResetPositionComponent(dae::GameObject* gameObject, glm::vec2 resetPosition);

	~ResetPositionComponent() override;
	ResetPositionComponent(const ResetPositionComponent& other) = delete;
	ResetPositionComponent(ResetPositionComponent&& other) = delete;
	ResetPositionComponent& operator=(const ResetPositionComponent& other) = delete;
	ResetPositionComponent& operator=(ResetPositionComponent&& other) = delete;

	void Update() override;
	void FixedUpdate() override;
	void Render() const override;

	

	void OnGlobalNotify(const std::string event) override;
	void OnNotify(dae::Subject* component, dae::Event event) override;
	void AddSubject(dae::Subject* subject) override;
	void InformAllSubjects(std::vector<dae::Subject*> subjects) override;

private:
	glm::vec2 m_ResetPosition;

	void ResetPosition() const;
};
