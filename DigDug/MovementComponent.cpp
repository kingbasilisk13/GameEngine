#include "MovementComponent.h"

#include "Renderer.h"

MovementComponent::MovementComponent(dae::GameObject* gameObject, float movementSpeed)
	:BaseComponent(gameObject)
	,m_MovementSpeed(movementSpeed)
{
	dae::Renderer::GetInstance().GetWindowSize(&m_WindowWidth, &m_WindowHeight);
}

void MovementComponent::Update()
{
	if (m_Direction == glm::vec2{})
	{
		return;
	}

	//calculate movement using time and speed.
	glm::vec2 deltaMovement = m_MovementSpeed * dae::EngineTime::GetInstance().GetDeltaTime() * glm::normalize(m_Direction);

	//get old position
	const auto position = GetOwningGameObject()->GetWorldPosition();

	//calculate new position
	auto newPosition = position + deltaMovement;

	//check if the player is not moving out of bounds.
	if(PerformProhibitedMovement(newPosition))
	{
		return;
	}

	const float radius = 1;


	if(m_Direction != m_LastDirection && m_Direction != (-m_LastDirection))
	{
		bool nearAPoint = false;
		//check direction. horizontal movment.
		if (m_LastDirection.x != 0)
		{
			for (const int xValue : m_XValues)
			{
				if (position.x > (xValue - radius) && position.x < (xValue + radius))
				{
					newPosition.x = static_cast<float>(xValue);
					newPosition.y = position.y;
					m_LastDirection = m_Direction;
					nearAPoint = true;
					break;
				}
			}
			if(!nearAPoint)
			{
				m_Direction = m_LastDirection;
				deltaMovement = m_MovementSpeed * dae::EngineTime::GetInstance().GetDeltaTime() * glm::normalize(m_LastDirection);
				newPosition = position + deltaMovement;
			}
		}
		else//vertical movement
		{
			for (const int yValue : m_YValues)
			{
				if (position.y > (yValue - radius) && position.y < (yValue + radius))
				{
					newPosition.y = static_cast<float>(yValue);
					newPosition.x = position.x;
					m_LastDirection = m_Direction;
					nearAPoint = true;
					break;
				}
			}
			if (!nearAPoint)
			{
				m_Direction = m_LastDirection;
				deltaMovement = m_MovementSpeed * dae::EngineTime::GetInstance().GetDeltaTime() * glm::normalize(m_LastDirection);
				newPosition = position + deltaMovement;
			}
		}
	}
	//else
	//{
	//	//check direction. horizontal movment.
	//	if (m_Direction.x != 0)
	//	{
	//		for (const int xValue : m_XValues)
	//		{
	//			if (position.x > (xValue - radius) && position.x < (xValue + radius))
	//			{
	//				auto p1 = glm::abs(xValue - position.x);
	//				auto p2 = glm::abs(xValue - newPosition.x);

	//				if (p2 < p1)
	//				{
	//					newPosition.x = static_cast<float>(xValue);
	//				}
	//				else
	//				{
	//					break;
	//				}
	//			}
	//		}
	//	}
	//	else//vertical movement
	//	{

	//	}
	//}

	GetOwningGameObject()->SetLocalPosition(newPosition);


	m_LastDirection = m_Direction;
	m_Direction = {};

}

void MovementComponent::FixedUpdate()
{
}

void MovementComponent::Render() const
{
}

void MovementComponent::SetMovementSpeed(const float movementSpeed)
{
	m_MovementSpeed = movementSpeed;
}

void MovementComponent::SetMovementDirection(const glm::vec2 direction)
{
	m_Direction = direction;
}

void MovementComponent::SetBounds(const glm::vec2 topLeft, const glm::vec2 bottomRight)
{
	m_TopLeftBoundPosition = topLeft;
	m_BottomRightBoundPosition = bottomRight;

	m_UseCustomBound = true;
}

void MovementComponent::SetGridValues(const std::vector<int>& xValues, const std::vector<int>& yValues)
{
	m_XValues = xValues;
	m_YValues = yValues;
}

bool MovementComponent::CheckPassingOverBounds(const glm::vec2 newPosition, const glm::vec2 topLeft, const glm::vec2 bottomRight)
{
	return (newPosition.x >= topLeft.x && newPosition.x <= bottomRight.x && newPosition.y >= topLeft.y && newPosition.y <= bottomRight.y);
}

bool MovementComponent::PerformProhibitedMovement(const glm::vec2 newPosition) const
{
	if (m_UseCustomBound)
	{
		if (!CheckPassingOverBounds(newPosition, m_TopLeftBoundPosition, m_BottomRightBoundPosition))
		{
			return true;
		}
	}
	else
	{
		if (!CheckPassingOverBounds(newPosition, glm::vec2(0, 0), glm::vec2(m_WindowWidth,m_WindowHeight)))
		{
			return true;
		}
	}
	return false;
}
