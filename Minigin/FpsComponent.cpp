#include "FpsComponent.h"

#include <format>
#include "Renderer.h"
#include "GameObject.h"
#include "TextComponent.h"


dae::FpsComponent::FpsComponent(GameObject* gameObject)
	: BaseComponent(gameObject)
	, m_FrameCount(0)
	, m_ElapsedTime(0.0f)
	, m_TextComponent(nullptr)
{
}

void dae::FpsComponent::Update()
{
	if(m_ComponentsAreDirty)
	{
		ReloadPointers();
	}
	if (m_TextComponent == nullptr)
	{
		return;
	}

	m_FrameCount++;
	
	m_ElapsedTime += Time::GetInstance().GetDeltaTime();

	if (m_ElapsedTime >= 1.0f) {
		const float fps = static_cast<float>(m_FrameCount) / m_ElapsedTime;

		m_TextComponent->ChangeText(std::format("{:.1f} FPS", fps));

		m_FrameCount = 0;
		m_ElapsedTime = 0.0f;
	}
}

void dae::FpsComponent::FixedUpdate()
{
}

void dae::FpsComponent::Render() const
{
}

void dae::FpsComponent::ReloadPointers()
{
	m_TextComponent = GetOwningGameObject()->GetComponent<TextComponent>();
	m_ComponentsAreDirty = false;
}
