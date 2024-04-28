#pragma once
#include "BaseComponent.h"
#include "IObserver.h"


namespace dae
{
	class TextComponent;
}

class PlayerObserverComponent final : public dae::BaseComponent, public dae::IObserver
{
public:
	explicit PlayerObserverComponent(dae::GameObject* gameObject);

	~PlayerObserverComponent() override;
	PlayerObserverComponent(const PlayerObserverComponent& other) = delete;
	PlayerObserverComponent(PlayerObserverComponent&& other) = delete;
	PlayerObserverComponent& operator=(const PlayerObserverComponent& other) = delete;
	PlayerObserverComponent& operator=(PlayerObserverComponent&& other) = delete;

	void Update() override;
	void FixedUpdate() override;
	void Render() const override;

	void OnNotify(dae::Subject* subject, dae::Event event) override;

	void AddSubject(dae::Subject* subject) override;
	void InformAllSubjects(std::vector<dae::Subject*> subjects) override;

private:
	dae::TextComponent* m_TextComponent;

	void ReloadPointers() override;

	std::vector<dae::Subject*> m_Subjects;

};

