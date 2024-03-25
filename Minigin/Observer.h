#pragma once
#include <vector>
#include "BaseComponent.h"

namespace dae
{
	//todo: interfaces hebben geen member variables.
	enum class Event
	{
		ActorDied,
		ScoreIncreased
	};

	class Observer
	{
		friend class Subject;
	public:
		virtual ~Observer();


		virtual void OnNotify(BaseComponent* component, Event event) = 0;

	private:
		//using this feels wrong but could not think of any better way to prevent nullpointers upon deletion of observer or subject.

		std::vector<Subject*> m_Subjects{};

		void AddSubject(Subject* subject);
		void RemoveSubject(const Subject* subject);
	};
}