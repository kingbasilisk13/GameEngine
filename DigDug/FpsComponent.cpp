#include "FpsComponent.h"
#include <format>
#include "Renderer.h"
#include "GameObject.h"
#include "TextComponent.h"


FpsComponent::FpsComponent(dae::GameObject* gameObject)
	: BaseComponent(gameObject)
	, m_FrameCount(0)
	, m_ElapsedTime(0.0f)
	, m_TextComponent(nullptr)
{
}

void FpsComponent::Update()
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
	
	m_ElapsedTime += dae::EngineTime::GetInstance().GetDeltaTime();

	if (m_ElapsedTime >= 1.0f) {
		const float fps = static_cast<float>(m_FrameCount) / m_ElapsedTime;

		m_TextComponent->ChangeText(std::format("{:.1f} FPS", fps));

		m_FrameCount = 0;
		m_ElapsedTime = 0.0f;
	}
}

void FpsComponent::FixedUpdate()
{
}

void FpsComponent::Render() const
{
}

void FpsComponent::ReloadPointers()
{
	m_TextComponent = GetOwningGameObject()->GetComponent<dae::TextComponent>();
	m_ComponentsAreDirty = false;
}
