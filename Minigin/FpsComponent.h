#pragma once
#include "BaseComponent.h"


namespace dae
{
	class TextComponent;
	class FpsComponent final : public BaseComponent
	{
	public:
		explicit FpsComponent(GameObject* gameObject);

		~FpsComponent() override = default;
		FpsComponent(const FpsComponent& other) = delete;
		FpsComponent(FpsComponent&& other) = delete;
		FpsComponent& operator=(const FpsComponent& other) = delete;
		FpsComponent& operator=(FpsComponent&& other) = delete;

		void Update() override;
		void FixedUpdate(float fixedTimeStep) override;
		void Render(float posX, float posY) const override;

	private:
		int m_FrameCount;
		float m_ElapsedTime;
		GameObject* m_Owner;
		TextComponent* m_TextComponent;

		void GetPointerToTextComponent();

	};
}
