#pragma once
#include "BaseComponent.h"
#include "IObserver.h"

namespace dae
{
	class TextComponent;
	class PlayerObserverComponent final : public BaseComponent, public IObserver
	{
	public:
		explicit PlayerObserverComponent(GameObject* gameObject);

		~PlayerObserverComponent() override;
		PlayerObserverComponent(const PlayerObserverComponent& other) = delete;
		PlayerObserverComponent(PlayerObserverComponent&& other) = delete;
		PlayerObserverComponent& operator=(const PlayerObserverComponent& other) = delete;
		PlayerObserverComponent& operator=(PlayerObserverComponent&& other) = delete;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void OnNotify(Subject* subject, Event event) override;

		void AddSubject(Subject* subject) override;
		void InformAllSubjects(std::vector<Subject*> subjects) override;

	private:
		TextComponent* m_TextComponent;

		void ReloadPointers() override;

		std::vector<Subject*> m_Subjects;

	};
}
