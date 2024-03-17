#include "ControllerWrapper.h"

#include <SDL_syswm.h>

dae::ControllerWrapper::ControllerWrapper(const int controllerIndex)
: m_controllerIndex(controllerIndex)
{
	
};

dae::ControllerWrapper::~ControllerWrapper() = default;

void dae::ControllerWrapper::Update()
{
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(m_controllerIndex, &m_CurrentState);
	const auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
	m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
}

bool dae::ControllerWrapper::IsDownThisFrame(unsigned int button) const
{
	return m_ButtonsPressedThisFrame & button;
}

bool dae::ControllerWrapper::IsUpThisFrame(unsigned int button) const
{
	return m_ButtonsReleasedThisFrame & button;
}

bool dae::ControllerWrapper::IsPressed(unsigned int button) const
{
	return m_CurrentState.Gamepad.wButtons & button;
}
