#pragma once
#include "BaseComponent.h"


//a component that is part of the engine self, used to render text and textures.
namespace dae
{
	class Texture2D;
	class RenderComponent final : public BaseComponent
	{
	public:
		explicit RenderComponent(GameObject* gameObject, std::shared_ptr<Texture2D> texture = nullptr);

		//texture is a shared pointer in case that multiple object require the same texture.

		~RenderComponent() override = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void ChangeTexture(std::shared_ptr<Texture2D> texture);

	private:
		std::shared_ptr<Texture2D> m_Texture;
	};
}