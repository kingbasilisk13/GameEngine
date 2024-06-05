#include "StateComponent.h"
#include "IState.h"

dae::StateComponent::StateComponent(GameObject* gameObject, IState* state)
	:BaseComponent(gameObject)
	,m_CurrentState(state)
{
}

dae::StateComponent::~StateComponent()
{
	delete m_CurrentState;
}

void dae::StateComponent::Update()
{
	IState* result = m_CurrentState->Update(GetOwningGameObject());

	if(result != nullptr)
	{
		m_CurrentState->OnExit();

		delete m_CurrentState;

		m_CurrentState = result;
		m_CurrentState->OnEnter(GetOwningGameObject());
	}
}

void dae::StateComponent::FixedUpdate()
{
}

void dae::StateComponent::Render() const
{
}

dae::IState* dae::StateComponent::GetCurrentState() const
{
	return m_CurrentState;
}
