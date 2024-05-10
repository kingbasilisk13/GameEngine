#pragma once

namespace dae
{
	class GameObject;
	class IState
	{
	public:
		
		virtual ~IState() = default;

		virtual IState* HandleInput(GameObject* owner) = 0;

		virtual IState* Update(GameObject* owner) = 0;

		virtual void OnEnter(GameObject* owner) = 0;

		virtual void OnExit() = 0;

	};


}
