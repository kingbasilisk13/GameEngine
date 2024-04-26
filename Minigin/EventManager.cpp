#include "EventManager.h"
#include <algorithm>
#include "IHandler.h"
#include "IObserver.h"


void dae::EventManager::Subscribe(EventType eventType, IHandler* handler)
{

	m_Events[eventType].push_back(handler);
}

void dae::EventManager::RemoveHandler(const IHandler* handler)
{
	for (const auto& test : m_Events)
	{
		EventType bob = test.first;

		UnSubscribe(bob, handler);
	}
}

void dae::EventManager::BroadcastEvent(EventType eventType, std::tuple<std::any> data)
{
	std::for_each(m_Events[eventType].begin(), m_Events[eventType].end(), [&](IHandler* handler)
	{
			handler->HandleEvent(eventType, data);
	});

}

void dae::EventManager::UnSubscribe(EventType eventType, const IHandler* handler)
{
	m_Events[eventType].erase(std::remove(m_Events[eventType].begin(), m_Events[eventType].end(), handler), m_Events[eventType].end());
}

