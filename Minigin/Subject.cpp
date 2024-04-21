#include "Subject.h"

dae::Subject::Subject(BaseComponent* owner)
: m_Owner(owner)
{
}

dae::Subject::~Subject()
{
	for (const auto observer : m_Observers)
	{
		observer->OnNotify(this, Event::SubjectIsDeleted);
	}
}

void dae::Subject::AddObserver(IObserver* observer)
{
	m_Observers.push_back(observer);
	observer->AddSubject(this);
}

void dae::Subject::RemoveObserver(const IObserver* observer)
{
	std::erase_if(m_Observers, [&](const IObserver* ptr)
		{
			if (ptr == observer)
			{
				return true;
			}
			return false;
		});
}

dae::BaseComponent* dae::Subject::GetOwner()
{
	return m_Owner;
}

void dae::Subject::Notify(const Event event)
{
	for (const auto observer : m_Observers)
	{
		observer->OnNotify(this, event);
	}
}