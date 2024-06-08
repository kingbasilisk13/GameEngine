#pragma once
#include <SDL.h>
#include <memory>
#include <SDL_syswm.h>
#include <string>

#include "Singleton.h"


namespace dae
{
	enum class ControllerInput;
	class Command;

	enum class KeyState {
		Down,
		Up,
		Pressed
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		[[nodiscard]] bool ProcessInput() const;

		void AddKeyBinding(std::unique_ptr<Command> command, const SDL_Scancode key, const KeyState keyState) const;

		void AddControllerBinding(
			std::unique_ptr<Command> command
			, const int controllerIndex
			, const ControllerInput button
			, const KeyState state) const;

		//removes all commands bound to a specifick scene.
		void RemoveBoundLevelCommands(const std::string& levelName) const;


	private:
		friend class Singleton<InputManager>;
		InputManager();

		class InputImpl;
		InputImpl* m_Pimpl = nullptr;

	};

}
