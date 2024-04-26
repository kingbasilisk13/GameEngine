#pragma once

#include <any>
#include "Minigin.h"
#include "Singleton.h"

//todo: find a way to pass arguments allong with the event.
namespace dae
{
	class IHandler;

	enum class EventType
	{
		playSound,
		playMusic
	};
	class IObserver;

	class EventManager final : public Singleton<EventManager>
	{
	public:

		void Subscribe(EventType eventType, IHandler* handler);

		void UnSubscribe(EventType eventType,const IHandler* handler);

		void RemoveHandler(const IHandler* handler);

		void BroadcastEvent(EventType eventType, std::tuple<std::any> data);
	private:
		friend class Singleton<EventManager>;
		EventManager() = default;

		//todo: voeg hier een map toe waar je specifieken handelers linkd aan specifieke events.
		//vb sound event word voor alles met sound gelinked.

		//todo: queue moet niet per see via de time ge de coupled worden. je mag ze gewoon direct uitvoeren. de keuze is aan u.

		std::unordered_map<EventType, std::vector<IHandler*>> m_Events;

	};
}
