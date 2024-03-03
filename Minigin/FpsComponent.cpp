#include "FpsComponent.h"

#include <format>
#include "Renderer.h"
#include "GameObject.h"
#include "TextComponent.h"


dae::FpsComponent::FpsComponent(GameObject* gameObject)
	: BaseComponent(gameObject)
	, m_FrameCount(0)
	, m_ElapsedTime(0.0f)
	, m_Owner(nullptr)
	, m_TextComponent(nullptr)
{
	m_Owner = GetOwningGameObject();
	GetPointerToTextComponent();
}

void dae::FpsComponent::Update()
{
	//todo: see if there is no cleaner way of making sure the object has a text component. still every frame asking for the component. other way?
	if(m_TextComponent == nullptr)
	{
		GetPointerToTextComponent();
		if (m_TextComponent == nullptr)
		{
			return;
		}
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

void dae::FpsComponent::FixedUpdate(float )
{
}

void dae::FpsComponent::Render(float , float ) const
{
}

void dae::FpsComponent::GetPointerToTextComponent()
{
	m_TextComponent = m_Owner->GetComponent<TextComponent>();
}
