#pragma once
#include "BaseComponent.h"


namespace dae
{
	class IState;

	class StateComponent final : public BaseComponent
	{
	public:
		explicit StateComponent(GameObject* gameObject, IState* state);

		~StateComponent() override;

		StateComponent(const StateComponent& other) = delete;
		StateComponent(StateComponent&& other) = delete;
		StateComponent& operator=(const StateComponent& other) = delete;
		StateComponent& operator=(StateComponent&& other) = delete;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		IState* GetCurrentState() const;

	private:
		IState* m_CurrentState;

	};
	
}


