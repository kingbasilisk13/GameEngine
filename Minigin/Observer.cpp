#include "Observer.h"
#include "Subject.h"

dae::Observer::~Observer()
{
	for (const auto subject : m_Subjects)
	{
		subject->RemoveObserver(this);
	}
}

void dae::Observer::AddSubject(Subject* subject)
{
	m_Subjects.push_back(subject);
}

void dae::Observer::RemoveSubject(const Subject* subject)
{
	std::erase_if(m_Subjects, [&](const Subject* ptr)
		{
			if (ptr == subject)
			{
				return true;
			}
			return false;
		});
}
