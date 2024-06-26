#pragma once
#include "BaseComponent.h"
#include "Rectf.h"
#include "utils.h"


namespace dae
{
	class BoxComponent final : public BaseComponent
	{
	public:
		explicit BoxComponent(GameObject* gameObject, float width, float height);

		~BoxComponent() override = default;

		BoxComponent(const BoxComponent& other) = delete;
		BoxComponent(BoxComponent&& other) = delete;
		BoxComponent& operator=(const BoxComponent& other) = delete;
		BoxComponent& operator=(BoxComponent&& other) = delete;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void ChangeDimensions(float width, float height);

		[[nodiscard]] Rectf GetBox();

		[[nodiscard]] Rectf GetFutureBox(glm::vec2) const;

	private:
		Rectf m_Box;
		
		[[nodiscard]] static Rectf ReCalculateBox(const glm::vec2 center, const float width, const float height);
	};
	
}


