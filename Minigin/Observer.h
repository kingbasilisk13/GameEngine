#pragma once

namespace dae
{
	class BaseComponent;
}

namespace dae
{
	enum class Event
	{
		ActorDied,
		ScoreIncreased
	};

	class Observer
	{
		class Entity;
		
	public:
		virtual  ~Observer() = default;
		virtual void OnNotify(BaseComponent* component, Event event) = 0;
	};
}


