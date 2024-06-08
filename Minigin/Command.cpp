#include "Command.h"

bool dae::Command::IsMarkedForDeletion() const
{
	return m_MarkedForDeletion;
}

void dae::Command::MarkedForDeletion()
{
	m_MarkedForDeletion = true;
}
