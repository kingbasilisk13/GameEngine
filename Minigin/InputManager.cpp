#include <SDL.h>
#include "InputManager.h"

#include <SDL_syswm.h>

#include <backends/imgui_impl_sdl2.h>

bool dae::InputManager::ProcessInput()
{
	
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	return true;
}
//add command neemt comand object en de knop waar het aan gebonden wordt.
//je hebt dus een mapping nodig