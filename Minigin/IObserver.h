#pragma once
#include <vector>
#include "BaseComponent.h"

namespace dae
{
	enum class Event
	{
		SubjectIsDeleted,
		ActorDied,
		ScoreIncreased
	};

	class IObserver
	{
		friend class Subject;
	public:
		virtual void OnNotify(Subject* component, Event event) = 0;

		//called when subscribing to a subject. Save a pointer to said subject in a vector.
		virtual void AddSubject(Subject* subject) = 0;

		//called when class implementing the interface is deleted. Warns all subjects that observer no longer exists.
		virtual void InformAllSubjects(std::vector<Subject*> subjects) = 0;
	};
}