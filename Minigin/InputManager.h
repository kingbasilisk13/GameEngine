#pragma once
#include <memory>
#include <unordered_map>

#include "Command.h"
#include "Singleton.h"



namespace dae
{
	struct KeyBinding {
		SDL_Scancode key;       // Keyboard key
		SDL_EventType eventType; // Key event type
		std::unique_ptr<dae::Command> command;

		KeyBinding(SDL_Scancode k, SDL_EventType e, std::unique_ptr<dae::Command> c)
			: key(k), eventType(e), command(std::move(c)) {}
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

		//scancode for the key, event type for pressed or released, keyboeard event for held.
		void AddKeyBinding(std::unique_ptr<Command> command, const SDL_Scancode key, const SDL_EventType state);

	private:
		//use sdl scancode because this is independant of the keyboard layout. if you pres a on a qwerty or azerty machine it should still work.
		//std::unordered_map<KeyBinding, std::unique_ptr<dae::Command>, KeyBinding::Hash> m_KeyBindingsMap;
		std::vector<KeyBinding> m_KeyBindings;

		std::vector<Command*> m_CommandsToExecute;
	};

}
