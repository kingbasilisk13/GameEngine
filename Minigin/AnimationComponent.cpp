#include "AnimationComponent.h"

#include "RenderComponent.h"

dae::AnimationComponent::AnimationComponent(GameObject* gameObject, float timeBetweenFrames, int numberOfRows, int numberOfColumns):
	BaseComponent(gameObject)
	, m_TimeBetweenFrames(timeBetweenFrames)
	, m_PassedTime(0)
	, m_NumberOfRows(numberOfRows)
	, m_NumberOfColumns(numberOfColumns)
{
}

void dae::AnimationComponent::Update()
{
	if(m_PlayAnimationOnce && (m_CurrentRowNumber+1) == m_NumberOfRows && (m_CurrentColumnNumber+1) == m_NumberOfColumns)
	{
		return;
	}

	if(m_PauseAnimation)
	{
		return;
	}

	const auto renderInfo = GetOwningGameObject()->GetComponent<RenderComponent>()->GetRenderInfo();
	const auto actualSize = renderInfo.textureToRender->GetSize();

	const int widthOfOneFrame = actualSize.x / m_NumberOfColumns;
	const int heightOfOneFrame = actualSize.y / m_NumberOfRows;


	m_PassedTime += EngineTime::GetInstance().GetDeltaTime();

	if(m_PassedTime >= m_TimeBetweenFrames)
	{
		m_PassedTime = 0;

		if(const auto renderComponent = GetOwningGameObject()->GetComponent<RenderComponent>())
		{
			++m_CurrentColumnNumber;

			if(m_CurrentColumnNumber >= m_NumberOfColumns)
			{
				m_CurrentColumnNumber = 0;
				++m_CurrentRowNumber;
			}

			if(m_CurrentRowNumber >= m_NumberOfRows)
			{
				m_CurrentRowNumber = 0;
			}

			renderComponent->ChangeSourceValues(
				(widthOfOneFrame * m_CurrentColumnNumber),
				(heightOfOneFrame * m_CurrentRowNumber),
				renderInfo.sourceWidth,
				renderInfo.sourceHeight);
		}
	}
}

void dae::AnimationComponent::FixedUpdate()
{
}

void dae::AnimationComponent::Render() const
{
}

void dae::AnimationComponent::PauseAnimation(bool pauseAnimation)
{
	m_PauseAnimation = pauseAnimation;
}

void dae::AnimationComponent::ChangeTimeBetweenFrames(const float time)
{
	m_TimeBetweenFrames = time;
	m_PassedTime = 0.f;
}

void dae::AnimationComponent::ChangeNumberOfRows(const int rows)
{
	m_NumberOfRows = rows;
	m_CurrentRowNumber = 0;
}

void dae::AnimationComponent::ChangeNumberOfColumns(const int columns)
{
	m_NumberOfColumns = columns;
	m_CurrentColumnNumber = 0;
}

void dae::AnimationComponent::SetPlayAnimationOnce(const bool playAnimationOnce)
{
	m_PlayAnimationOnce = playAnimationOnce;
}
