#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace dae
{
	class TextComponent;
	class PlayerObserverComponent final : public BaseComponent, public Observer
	{
	public:
		explicit PlayerObserverComponent(GameObject* gameObject);

		~PlayerObserverComponent() override = default;
		PlayerObserverComponent(const PlayerObserverComponent& other) = delete;
		PlayerObserverComponent(PlayerObserverComponent&& other) = delete;
		PlayerObserverComponent& operator=(const PlayerObserverComponent& other) = delete;
		PlayerObserverComponent& operator=(PlayerObserverComponent&& other) = delete;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void OnNotify(BaseComponent* component, Event event) override;

	private:
		TextComponent* m_TextComponent;

		void ReloadPointers() override;

	};
}
