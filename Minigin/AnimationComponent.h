#pragma once
#include "BaseComponent.h"

namespace dae
{
	//a simple component that creates animation by going over the sprites in a sprite sheet in row colum order. from top left to bottem right.
	class AnimationComponent final : public BaseComponent
	{
	public:
		explicit AnimationComponent( 
			GameObject* gameObject
			, float timeBetweenFrames
			, int numberOfRows
			, int numberOfColumns
		);

		~AnimationComponent() override = default;

		AnimationComponent(const AnimationComponent& other) = delete;
		AnimationComponent(AnimationComponent&& other) = delete;
		AnimationComponent& operator=(const AnimationComponent& other) = delete;
		AnimationComponent& operator=(AnimationComponent&& other) = delete;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void PauseAnimation(bool pauseAnimation);

		void ChangeTimeBetweenFrames(const float time);

		void ChangeNumberOfRows(const int rows);
		void ChangeNumberOfColumns(const int columns);

		void SetPlayAnimationOnce(const bool playAnimationOnce);

	private:
		bool m_PauseAnimation = false;

		bool m_PlayAnimationOnce = false;

		float m_TimeBetweenFrames;
		float m_PassedTime;

		int m_NumberOfRows;
		int m_NumberOfColumns;

		int m_CurrentRowNumber = 0;
		int m_CurrentColumnNumber = 0;
	};
}

