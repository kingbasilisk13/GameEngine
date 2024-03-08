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
		void FixedUpdate() override;
		void Render() const override;

	private:
		int m_FrameCount;
		float m_ElapsedTime;
		TextComponent* m_TextComponent;

		void ReloadPointers() override;

	};
}
