#include "EngineTime.h"

float dae::EngineTime::GetDeltaTime() const
{
	return m_DeltaTime;
}

float dae::EngineTime::GetFixedTimeStep() const
{
	return m_FixedTimeStep;
}

void dae::EngineTime::ChangeDeltaTime(const float deltaTime)
{ m_DeltaTime = deltaTime; }

void dae::EngineTime::SetFixedTimeStep(const float fixedTimeStep)
{ m_FixedTimeStep = fixedTimeStep; }
