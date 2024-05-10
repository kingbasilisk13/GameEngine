#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"


//a component that is part of the engine self, used to render text and textures.
namespace dae
{
	//a component that renders a texture on the same position as the game object.
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

		//when true draws the image using the size of the image.
		void SizeToContent(const bool sizeToContent);

		//the order in witch to draw the image. lower z = background, higher = foreground.
		void SetZOrder(int zOrder);

		//the part of the image that will be drawn.
		void SetSourceValues(int x, int y, int width, int height);


	private:
		bool m_SizeToContent;

		int m_ZOrder;

		int m_DestinationWidth;
		int m_DestinationHeight;

		int m_SourcePositionX;
		int m_SourcePositionY;
		int m_SourceWidth;
		int m_SourceHeight;

		Texture2D* m_Texture;
	};
}