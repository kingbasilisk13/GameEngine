#include "TimerComponent.h"

#include "FpsComponent.h"
#include "RenderComponent.h"
#include "Scene.h"

dae::TimerComponent::TimerComponent(GameObject* gameObject)
	:BaseComponent(gameObject)
{
}

void dae::TimerComponent::Update()
{

	if(m_TaskFinished == false)
	{
		m_ElapsedTime += dae::EngineTime::GetInstance().GetDeltaTime();

		if(m_ElapsedTime >= 10.f)
		{
			const auto gameObject = GetOwningGameObject();
			//gameObject->RemoveComponent(gameObject->GetComponent<FpsComponent>());
			//gameObject->RemoveComponent(gameObject->GetComponent<RenderComponent>());

			gameObject->GetScene()->Remove(gameObject);
			m_TaskFinished = true;
		}
	}
}

void dae::TimerComponent::FixedUpdate()
{
}

void dae::TimerComponent::Render() const
{
}
