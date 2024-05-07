#pragma once
#include "BaseComponent.h"

#include <utility>
#include "Renderer.h"
#include "Texture2D.h"

//todo: vervange dit component door een service die iedereen kan gebruikne.
//todo: denk na over een struct waar je alle image info in steekt en de layer (vb int value) dat aangeeft of het voor of achteraan moet getekent worden.

//a component that is part of the engine self, used to render text and textures.
namespace dae
{
	class RenderComponent final : public BaseComponent
	{
	public:
		explicit RenderComponent(GameObject* gameObject, Texture2D* texture = nullptr);

		~RenderComponent() override = default;

		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void ChangeTexture(Texture2D* texture);

	private:
		Texture2D* m_Texture;
	};
}