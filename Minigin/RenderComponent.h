#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"

//a component that is part of the engine self, used to render text and textures.
namespace dae
{
	enum class FlipImage
	{
		None,
		Horizontaly,
		Verticaly
	};

	struct RenderInfo
	{
		int zOrder = 0;

		//will be replaced with position of owning object.
		int destinationX = 0;
		//will be replaced with position of owning object.
		int destinationY = 0;

		int destinationWidth = 0;
		int destinationHeight = 0;
		int sourceX = 0;
		int sourceY = 0;
		int sourceWidth = 0;
		int sourceHeight = 0;
		float angle = 0;
		Texture2D* textureToRender = nullptr;
		FlipImage imageFlip = FlipImage::None;
	};

	

	//a component that renders a texture on the same position as the game object.
	class RenderComponent final : public BaseComponent
	{
	public:
		explicit RenderComponent(
			GameObject* gameObject, RenderInfo renderInfo);

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

		//the part of the image that will be drawn.
		void ChangeDestinationPosition(int x, int y);

		void ChangeImageFlip(FlipImage imageFlip);

		void ChangeAngle(float angle);

		RenderInfo GetRenderInfo() const;

	private:
		RenderInfo m_RenderInfo;

		glm::vec2 m_OwnerPosition;

		void ShiftToCenter();
	};
}