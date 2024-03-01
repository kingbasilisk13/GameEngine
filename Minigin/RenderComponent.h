#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Texture2D;
	class RenderComponent final : public BaseComponent
	{
	public:
		explicit RenderComponent(GameObject* gameObject, std::shared_ptr<Texture2D> texture = nullptr);

		~RenderComponent() override = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		void Update() override;
		void FixedUpdate(float fixedTimeStep) override;
		void Render(float posX, float posY) const override;

		void ChangeTexture(std::shared_ptr<Texture2D> texture);

	private:
		//render components owns the texture, so it is responsoble for handeling it.
		std::shared_ptr<Texture2D> m_Texture;
		
	};
}