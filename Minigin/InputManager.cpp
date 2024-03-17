#include <SDL.h>
#include "InputManager.h"
#include <iostream>
#include <SDL_syswm.h>
#include <backends/imgui_impl_sdl2.h>
#include "Command.h"
#include <Xinput.h>

class dae::InputManager::InputImpl
{
public:
	InputImpl()
	{
		for (int i = 0; i < 4; ++i)
		{
			m_Controllers[i] = std::make_unique<ControllerWrapper>(i);
		}
	};
	~InputImpl() = default;

	void ProcessInput()
	{
		// Copy current state to previous state
		SDL_memcpy(m_PreviousState, m_CurrentState, SDL_NUM_SCANCODES);
		// Update current state
		SDL_memcpy(m_CurrentState, SDL_GetKeyboardState(nullptr), SDL_NUM_SCANCODES);

		for (int i = 0; i < 4; ++i)
		{
			m_Controllers[i]->Update();
		}

		for (const auto& controllerBinding : m_ControllerBindings)
		{
			switch (controllerBinding.keyState)
			{
			case KeyState::Down:
				if (m_Controllers[controllerBinding.controllerIndex]->IsDownThisFrame(controllerBinding.button))
				{
					m_CommandsToExecute.push_back(controllerBinding.command.get());
				}
				break;
			case KeyState::Up:
				if (m_Controllers[controllerBinding.controllerIndex]->IsUpThisFrame(controllerBinding.button))
				{
					m_CommandsToExecute.push_back(controllerBinding.command.get());
				}
				break;
			case KeyState::Pressed:
				if (m_Controllers[controllerBinding.controllerIndex]->IsPressed(controllerBinding.button))
				{
					m_CommandsToExecute.push_back(controllerBinding.command.get());
				}
				break;
			}
		}

		for (const auto& keyBinding : m_KeyBindings)
		{
			switch (keyBinding.state)
			{
			case KeyState::Down:
				if (IsDownThisFrame(keyBinding.key))
				{
					m_CommandsToExecute.push_back(keyBinding.command.get());
				}
				break;
			case KeyState::Up:
				if (IsUpThisFrame(keyBinding.key))
				{
					m_CommandsToExecute.push_back(keyBinding.command.get());
				}
				break;
			case KeyState::Pressed:
				if (IsPressed(keyBinding.key))
				{
					m_CommandsToExecute.push_back(keyBinding.command.get());
				}
				break;
			}
		}

		for (Command* command : m_CommandsToExecute)
		{
			command->Execute();
		}
		m_CommandsToExecute.clear();
	}

	void AddKeyBinding(std::unique_ptr<Command> command, const SDL_Scancode key, const KeyState keyState)
	{
		m_KeyBindings.emplace_back(key, keyState, std::move(command));
	}

	void AddControllerBinding(std::unique_ptr<Command> command, const int controllerIndex, const WORD button, const KeyState state)
	{
		m_ControllerBindings.emplace_back(controllerIndex, button, state, std::move(command));
	}

private:
	struct KeyBinding
	{
		SDL_Scancode key; // Keyboard key
		KeyState state; // Key event type
		std::unique_ptr<dae::Command> command; //bound command
	};

	struct ControllerBinding
	{
		int controllerIndex; // Index of the controller (0-3)
		WORD button; // Button ID (XINPUT_GAMEPAD_A, XINPUT_GAMEPAD_B, etc.)
		KeyState keyState; // Key state (Down, Up, Pressed)
		std::unique_ptr<dae::Command> command; // command bound to key
	};

	std::vector<KeyBinding> m_KeyBindings{};
	std::vector<ControllerBinding> m_ControllerBindings{};
	std::vector<Command*> m_CommandsToExecute{};

	std::unique_ptr<ControllerWrapper> m_Controllers[4];

	Uint8 m_PreviousState[SDL_NUM_SCANCODES]{};
	Uint8 m_CurrentState[SDL_NUM_SCANCODES]{};



	bool IsDownThisFrame(const SDL_Scancode key) const
	{
		return m_CurrentState[key] && !m_PreviousState[key];
	}

	bool IsUpThisFrame(const SDL_Scancode key) const
	{
		return !m_CurrentState[key] && m_PreviousState[key];
	}

	bool IsPressed(const SDL_Scancode key) const
	{
		return m_CurrentState[key];
	}
};

void dae::InputManager::Initialize()
{
	if (m_Pimpl == nullptr)
	{
		m_Pimpl = new InputImpl();
	}

	

}

bool dae::InputManager::ProcessInput() const
{
	m_Pimpl->ProcessInput();

	SDL_Event e;
	while (SDL_PollEvent(&e)) 
	{
		if (e.type == SDL_QUIT) 
		{
			delete m_Pimpl;
			return false;
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) 
		{
		}

		ImGui_ImplSDL2_ProcessEvent(&e);
	}
	return true;
}

void dae::InputManager::AddKeyBinding(std::unique_ptr<Command> command, const SDL_Scancode key,
	const KeyState keyState) const
{
	m_Pimpl->AddKeyBinding(std::move(command), key, keyState);
}

void dae::InputManager::AddControllerBinding(std::unique_ptr<Command> command, const int controllerIndex, const WORD button, const KeyState state) const
{
	m_Pimpl->AddControllerBinding(std::move(command), controllerIndex, button,state);
}