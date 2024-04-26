#pragma once
#include <any>

namespace dae
{
	enum class EventType;

	
	class IHandler
	{
	public:
		//make sure that the dataTuple has the correct info.
		virtual void HandleEvent(const EventType event, std::tuple<std::any> data) = 0;

		//call this event when object is being deleted.
		virtual void HandleDeletion() = 0;
	};
}
