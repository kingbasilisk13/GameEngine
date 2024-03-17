#pragma once
#include<windows.h>
#include <Xinput.h>

namespace dae
{
	class ControllerWrapper
	{
	public:
		ControllerWrapper(const int controllerIndex);

		~ControllerWrapper();

		ControllerWrapper(const ControllerWrapper&) = delete;
		ControllerWrapper(ControllerWrapper&&) = delete;
		ControllerWrapper& operator= (const ControllerWrapper&) = delete;
		ControllerWrapper& operator= (const ControllerWrapper&&) = delete;

		void Update();

		bool IsDownThisFrame(unsigned int button) const;
		bool IsUpThisFrame(unsigned int button) const;
		bool IsPressed(unsigned int button) const;

	private:
		int m_controllerIndex; // Index of the controller
		XINPUT_STATE m_CurrentState; // Current state of the controller
		XINPUT_STATE m_PreviousState; // Previous state of the controller

		int m_ButtonsPressedThisFrame;
		int m_ButtonsReleasedThisFrame;
	};
}



