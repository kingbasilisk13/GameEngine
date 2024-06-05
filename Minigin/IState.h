#pragma once

namespace dae
{
	class GameObject;
	class IState
	{
	public:
		
		virtual ~IState() = default;

		//removed because this is only usefull for the player. users will have to create this themselfs and add their choise of input along with it.
		//virtual IState* HandleInput(GameObject* owner) = 0;

		virtual IState* Update(GameObject* owner) = 0;

		virtual void OnEnter(GameObject* owner) = 0;

		virtual void OnExit() = 0;

	};


}
