#include "EventManager.h"
#include <algorithm>
#include "IObserver.h"


void dae::EventManager::Subscribe(IObserver* observer)
{
	m_Observers.push_back(observer);
}

void dae::EventManager::BroadcastEvent(const std::string& event)
{
	RemoveDeletedObservers();
	for (const auto observer : m_Observers)
	{
		if(observer != nullptr)
		{
			observer->OnGlobalNotify(event);
		}
	}
	RemoveDeletedObservers();
}

void dae::EventManager::RemoveDeletedObservers()
{
	for (auto observersMarkedForDeletion : m_ObserversMarkedForDeletion)
	{
		std::erase(m_Observers, observersMarkedForDeletion);
	}
	m_ObserversMarkedForDeletion.clear();
}

void dae::EventManager::UnSubscribe(IObserver* observer)
{
	m_ObserversMarkedForDeletion.emplace_back(observer);
}

