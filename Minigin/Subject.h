#pragma once
#include <vector>
#include "IObserver.h"

namespace dae
{
	//An object that can be subscribed to
	class Subject final
	{
	public:
		explicit Subject(BaseComponent* owner);

		~Subject();

		Subject(const Subject& other) = delete;
		Subject(Subject&& other) = delete;
		Subject& operator=(const Subject& other) = delete;
		Subject& operator=(Subject&& other) = delete;

		void AddObserver(IObserver* observer);

		void RemoveObserver(const IObserver* observer);

		void Notify(Event event);

		BaseComponent* GetOwner();
	private:
		BaseComponent* m_Owner;

		std::vector<IObserver*> m_Observers{};

	};
}