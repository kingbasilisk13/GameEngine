

#include "ControllerWrapper.h"

#include <SDL_syswm.h>
#include <Xinput.h>

#include "InputManager.h"

class dae::ControllerWrapper::ControllerImpl
{
public:
	explicit ControllerImpl(const int controllerIndex)
		:m_controllerIndex(controllerIndex)
	{
		
	}

	void Update()
	{
		CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		XInputGetState(m_controllerIndex, &m_CurrentState);
		const auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
		m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
	}

	[[nodiscard]] bool CheckButtonState(const KeyState keyState, unsigned int button) const
	{
		switch (keyState)
		{
		case KeyState::Down:
			return IsDownThisFrame(button);
		case KeyState::Up:
			return IsUpThisFrame(button);
		case KeyState::Pressed:
			return IsPressed(button);
		}
		return false;
	}

private:
	[[nodiscard]] bool IsDownThisFrame(const unsigned int button) const
	{
		return m_ButtonsPressedThisFrame & button;
	}

	[[nodiscard]] bool IsUpThisFrame(const unsigned int button) const
	{
		return m_ButtonsReleasedThisFrame & button;
	}

	[[nodiscard]] bool IsPressed(const unsigned int button) const
	{
		return m_CurrentState.Gamepad.wButtons & button;
	}


	int m_controllerIndex{}; // Index of the controller
	XINPUT_STATE m_CurrentState{}; // Current state of the controller
	XINPUT_STATE m_PreviousState{}; // Previous state of the controller

	int m_ButtonsPressedThisFrame{};
	int m_ButtonsReleasedThisFrame{};
};



dae::ControllerWrapper::ControllerWrapper(const int controllerIndex)
{
	m_Pimpl = new ControllerImpl(controllerIndex);
};

dae::ControllerWrapper::~ControllerWrapper()
{
	delete m_Pimpl;
}

void dae::ControllerWrapper::Update() const
{
	m_Pimpl->Update();
}

bool dae::ControllerWrapper::CheckButtonState(const KeyState keyState, const unsigned int button) const
{
	return m_Pimpl->CheckButtonState(keyState, button);
}
