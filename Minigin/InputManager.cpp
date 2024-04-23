#include "InputManager.h"
#include <SDL_keyboard.h>
#include <SDL_scancode.h>
#include <SDL_stdinc.h>
#include <SDL_syswm.h>
#include <vector>
#include "ControllerWrapper.h"
#include "imgui_impl_sdl2.h"
#include <SDL_events.h>
#include "Command.h"

//todo: ask if now that XInput.h is gone that it is correct?
class dae::InputManager::InputImpl
{
public:
	InputImpl()
	{
		for (int i = 0; i < 4; ++i)
		{
			m_Controllers[i] = std::make_unique<ControllerWrapper>(i);
		}
	}

	~InputImpl() = default;

	InputImpl(const InputImpl&) = delete;
	InputImpl(InputImpl&&) = delete;
	InputImpl& operator= (const InputImpl&) = delete;
	InputImpl& operator= (const InputImpl&&) = delete;

	void ProcessInput()
	{
		// Copy current state to previous state
		SDL_memcpy(m_PreviousState, m_CurrentState, SDL_NUM_SCANCODES);
		// Update current state
		SDL_memcpy(m_CurrentState, SDL_GetKeyboardState(nullptr), SDL_NUM_SCANCODES);

		for (const auto& controller : m_Controllers)
		{
			controller->Update();
		}

		for (const auto& [controllerIndex, button, keyState, command] : m_ControllerBindings)
		{
			if(m_Controllers[controllerIndex]->CheckButtonState(keyState, button))
			{
				m_CommandsToExecute.push_back(command.get());
			}
		}

		for (const auto& [key, state, command] : m_KeyBindings)
		{
			switch (state)
			{
			case KeyState::Down:
				if (IsDownThisFrame(key))
				{
					m_CommandsToExecute.push_back(command.get());
				}
				break;
			case KeyState::Up:
				if (IsUpThisFrame(key))
				{
					m_CommandsToExecute.push_back(command.get());
				}
				break;
			case KeyState::Pressed:
				if (IsPressed(key))
				{
					m_CommandsToExecute.push_back(command.get());
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

	void AddControllerBinding(
		std::unique_ptr<Command> command
		, const int controllerIndex
		, const ControllerInput button
		, const KeyState state)
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
		ControllerInput button; // Button ID (XINPUT_GAMEPAD_A, XINPUT_GAMEPAD_B, etc.)
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

void dae::InputManager::AddControllerBinding(
	std::unique_ptr<Command> command
	, const int controllerIndex
	, const ControllerInput button
	, const KeyState state) const
{
	m_Pimpl->AddControllerBinding(std::move(command), controllerIndex, button,state);
}

dae::InputManager::InputManager()
{
	if (m_Pimpl == nullptr)
	{
		m_Pimpl = new InputImpl();
	}
}
