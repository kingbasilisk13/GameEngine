#pragma once
#include "Singleton.h"
#include "Minigin.h"


//todo: this does not work yet. do not use this.
namespace dae
{
	class IObserver;

	//like a subject but on a global level.
	class EventManager final : public Singleton<EventManager>
	{
	public:
		void Subscribe(IObserver* observer);

		void UnSubscribe(IObserver* observer);

		//simple event system. broadcast a string starting with a specific name and all the required values seperated by a ;.
		void BroadcastEvent(const std::string& event);

	private:
		friend class Singleton<EventManager>;
		EventManager() = default;

		std::vector<IObserver*> m_Observers{};

		std::vector<IObserver*> m_ObserversMarkedForDeletion{};

		void RemoveDeletedObservers();
	};
}
