#pragma once

#include <queue>

#include "Minigin.h"
#include "Singleton.h"

namespace dae
{
	enum class Event;
	class IObserver;

	class EventManager final : public Singleton<EventManager>
	{
	public:
		void SendEvent(Event event);

		void Subscribe(IObserver* observer);

		void UnSubscribe(const IObserver* observer);


	private:
		//only minigin is allowed to call procesEvent
		friend void dae::Minigin::Run(const std::function<void()>& load) const;

		friend class Singleton<EventManager>;
		EventManager() = default;

		void ProcessEvent();

		std::queue<Event> m_EventQueue;
		std::vector<IObserver*> m_Observers;

	};
}
