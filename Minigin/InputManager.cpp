#include <SDL.h>
#include "InputManager.h"

#include <iostream>
#include <SDL_syswm.h>

#include <backends/imgui_impl_sdl2.h>

#include "Command.h"


bool dae::InputManager::ProcessInput()
{
	
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);

	for(const auto& keyBinding : m_KeyBindings)
	{
		if(keyboardState[keyBinding.key])
		{
			m_CommandsToExecute.push_back(keyBinding.command.get());
		}
	}

	for(Command* command : m_CommandsToExecute)
	{
		command->Execute();
	}

	m_CommandsToExecute.clear();

	return true;
}

void dae::InputManager::AddKeyBinding(std::unique_ptr<Command> command, const SDL_Scancode key, const SDL_EventType state)
{
	m_KeyBindings.push_back(KeyBinding(key, state, std::move(command)));
}

//add command neemt comand object en de knop waar het aan gebonden wordt.
//je hebt dus een mapping nodig