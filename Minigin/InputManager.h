#pragma once
#include <memory>
#include <unordered_map>
#include "Command.h"
#include "ControllerWrapper.h"
#include "Singleton.h"



namespace dae
{
	enum class KeyState {
		Down,
		Up,
		Pressed
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		void Initialize();

		[[nodiscard]] bool ProcessInput() const;

		void AddKeyBinding(std::unique_ptr<Command> command, const SDL_Scancode key, const KeyState keyState) const;

		void AddControllerBinding(std::unique_ptr<Command> command, const int controllerIndex, const WORD button, const KeyState state) const;

	private:
		class InputImpl;
		InputImpl* m_Pimpl = nullptr;

	};

}