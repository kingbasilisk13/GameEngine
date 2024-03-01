#include "FpsComponent.h"

#include <format>
#include <stdexcept>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "GameObject.h"
#include "TextComponent.h"

dae::FpsComponent::FpsComponent(GameObject* gameObject)
	: BaseComponent(gameObject)
	, m_FrameCount(0)
	, m_ElapsedTime(0.0f)
{
}

//todo: ask a reference to text component outside the update loop and pass the fps text to it to be rendered.
//todo: check if value actually changed before passing to different function.
void dae::FpsComponent::Update()
{
	m_FrameCount++;
	
	m_ElapsedTime += Time::GetInstance().GetDeltaTime();

	if (m_ElapsedTime >= 1.0f) {
		const float fps = static_cast<float>(m_FrameCount) / m_ElapsedTime;
		;
		GetOwningGameObject().GetComponent<TextComponent>()->ChangeText(std::format("{:.1f} FPS", fps));

		m_FrameCount = 0;
		m_ElapsedTime = 0.0f;
	}
}

void dae::FpsComponent::FixedUpdate(float )
{
}

void dae::FpsComponent::Render(float , float ) const
{
}