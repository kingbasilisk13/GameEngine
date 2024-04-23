#include "ControllerWrapper.h"
#include <SDL_syswm.h>
#include "InputManager.h"
#include "ControllerInput.h"
#include <Xinput.h>

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

	[[nodiscard]] bool CheckButtonState(const KeyState keyState, ControllerInput button) const
	{
		const unsigned int actualButton = TranslateButton(button);
		switch (keyState)
		{
		case KeyState::Down:
			return IsDownThisFrame(actualButton);
		case KeyState::Up:
			return IsUpThisFrame(actualButton);
		case KeyState::Pressed:
			return IsPressed(actualButton);
		}
		return false;
	}

private:
	static unsigned int TranslateButton(ControllerInput button)
	{
		unsigned int result{};

		switch (button)
		{
		case ControllerInput::Gamepad_A:
			result = XINPUT_GAMEPAD_A;
			break;
		case ControllerInput::Gamepad_B:
			result = XINPUT_GAMEPAD_B;
			break;
		case ControllerInput::Gamepad_X:
			result = XINPUT_GAMEPAD_X;
			break;
		case ControllerInput::Gamepad_Y:
			result = XINPUT_GAMEPAD_Y;
			break;
		case ControllerInput::Gamepad_Dpad_Up:
			result = XINPUT_GAMEPAD_DPAD_UP;
			break;
		case ControllerInput::Gamepad_Dpad_Down:
			result = XINPUT_GAMEPAD_DPAD_DOWN;
			break;
		case ControllerInput::Gamepad_Dpad_Left:
			result = XINPUT_GAMEPAD_DPAD_LEFT;
			break;
		case ControllerInput::Gamepad_Dpad_Right:
			result = XINPUT_GAMEPAD_DPAD_RIGHT;
			break;
		default: ;
		}
		return result;
	}

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

bool dae::ControllerWrapper::CheckButtonState(const KeyState keyState, ControllerInput button) const
{
	return m_Pimpl->CheckButtonState(keyState, button);
}
