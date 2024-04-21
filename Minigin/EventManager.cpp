#include "EventManager.h"

#include "IObserver.h"

void dae::EventManager::SendEvent(Event event)
{
	m_EventQueue.push(event);
}

void dae::EventManager::Subscribe(IObserver* observer)
{
	m_Observers.push_back(observer);
}

void dae::EventManager::UnSubscribe(const IObserver* observer)
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

void dae::EventManager::ProcessEvent()
{
	if(!m_EventQueue.empty())
	{
		const Event event = m_EventQueue.front();
		m_EventQueue.pop();
		for (const auto observer : m_Observers)
		{
			observer->OnNotify(nullptr, event);
		}
	}
	
}
