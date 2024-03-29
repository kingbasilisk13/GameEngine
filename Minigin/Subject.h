#pragma once
#include <vector>
#include "Observer.h"

namespace dae
{
	//todo: interfaces hebben geen member variables.
	class Subject
	{
	public:

		virtual ~Subject();
		void AddObserver(Observer* observer);

		void RemoveObserver(const Observer* observer);

	protected:
		void Notify(BaseComponent* component, Event event) const;

	private:
		std::vector<Observer*> m_Observers{};

	};
}