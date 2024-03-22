#include "Subject.h"

void dae::Subject::AddObserver(Observer* observer)
{
	m_Observers.push_back(observer);
}

void dae::Subject::RemoveObserver(const Observer* observer)
{
	std::erase_if(m_Observers, [&](const Observer* ptr)
		{
			if (ptr == observer)
			{
				return true;
			}
			return false;
		});
}

void dae::Subject::Notify(BaseComponent* component,const Event event) const
{
	for(const auto observer : m_Observers)
	{
		observer->OnNotify(component, event);
	}
}
