#include "TimerComponent.h"

#include "FpsComponent.h"

#include "Scene.h"

TimerComponent::TimerComponent(dae::GameObject* gameObject)
	:BaseComponent(gameObject)
{
}

void TimerComponent::Update()
{

	if(m_TaskFinished == false)
	{
		m_ElapsedTime += dae::EngineTime::GetInstance().GetDeltaTime();

		if(m_ElapsedTime >= 10.f)
		{
			const auto gameObject = GetOwningGameObject();


			gameObject->GetScene()->Remove(gameObject);
			m_TaskFinished = true;
		}
	}
}

void TimerComponent::FixedUpdate()
{
}

void TimerComponent::Render() const
{
}
