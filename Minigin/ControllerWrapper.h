#pragma once

namespace dae
{
	enum class KeyState;

	class ControllerWrapper
	{
	public:
		explicit ControllerWrapper(const int controllerIndex);

		~ControllerWrapper();

		ControllerWrapper(const ControllerWrapper&) = delete;
		ControllerWrapper(ControllerWrapper&&) = delete;
		ControllerWrapper& operator= (const ControllerWrapper&) = delete;
		ControllerWrapper& operator= (const ControllerWrapper&&) = delete;

		void Update() const;

		[[nodiscard]] bool CheckButtonState(KeyState keyState, unsigned int button) const;

	private:
		class ControllerImpl;
		ControllerImpl* m_Pimpl = nullptr;
	};
}



