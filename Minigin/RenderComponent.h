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
		explicit RenderComponent(
			GameObject* gameObject, 
			int zOrder,
			int destinationWidth,
			int destinationHeight,
			int sourceX,
			int sourceY,
			int sourceWidth,
			int sourceHeight,
			Texture2D* texture = nullptr);

		~RenderComponent() override = default;

		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void ChangeTexture(Texture2D* texture);

		//the order in witch to draw the image. lower z = background, higher = foreground.
		void ChangeZOrder(int zOrder);

		//the part of the image that will be drawn.
		void ChangeSourceValues(int x, int y, int width, int height);

		//the part of the image that will be drawn.
		void ChangeDestinationSize(int width, int height);


	private:
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