#pragma once
#include "BaseComponent.h"

#include <string>
#include <memory>
#include "Transform.h"

#include <iostream>
#include <chrono>

struct SDL_Texture;
namespace dae
{
	class Font;

	class FpsComponent final : public BaseComponent
	{
	public:
		FpsComponent(GameObject* gameObject, std::shared_ptr<Font> font);

		virtual ~FpsComponent();
		FpsComponent(const FpsComponent& other) = delete;
		FpsComponent(FpsComponent&& other) = delete;
		FpsComponent& operator=(const FpsComponent& other) = delete;
		FpsComponent& operator=(FpsComponent&& other) = delete;

		void Update() override;
		void FixedUpdate(float fixedTimeStep) override;
		void Render(float posX, float posY) const override;

	private:
		std::shared_ptr<Font> m_Font;
		SDL_Texture* m_Texture;

		std::chrono::high_resolution_clock::time_point m_LastFrameTime;
		int m_FrameCount;
		float m_ElapsedTime;

		void GenerateTexture(const std::string &text);
	};
}
