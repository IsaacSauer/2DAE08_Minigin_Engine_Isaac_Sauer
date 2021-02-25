#pragma once
#include <map>
#include <XInput.h>

#include "Command.h"
#include "Controller.h"
#include "Singleton.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		using ControllerKeyType = std::pair<unsigned, std::pair<Controller::ControllerButton, Controller::ButtonState>>;
		using CommandState = std::pair<std::unique_ptr<Command>, bool>;
		using ControllerCommandsMap = std::map<ControllerKeyType, CommandState>;

		bool ProcessInput();
		bool IsButtonDown(Controller::ControllerButton button, UINT controllerId = 0) const;
		bool IsButtonPressed(Controller::ControllerButton button, UINT controllerId = 0) const;
		bool IsButtonReleased(Controller::ControllerButton button, UINT controllerId = 0) const;

		template <typename T>
		bool AddCommand(ControllerKeyType key, std::unique_ptr<T> upCommand);
		UINT AddController();

		static ControllerKeyType ControllerKey(UINT id, Controller::ControllerButton button,
			Controller::ButtonState state = Controller::ButtonState::REPEAT);
	private:
		ControllerCommandsMap m_ControllerCommands{};
		std::vector<std::unique_ptr<Controller>> m_Controllers{};
	};

	//Macros
	#define Command(commandName) std::move(std::make_unique<commandName>(commandName{}))
	#define CommandToObject(commandName, gameObj) std::move(std::make_unique<commandName>(commandName{gameObj}))

	#define INPUTMANAGER dae::ResourceManager::GetInstance()

}

template<typename T>
inline bool dae::InputManager::AddCommand(ControllerKeyType key, std::unique_ptr<T> upCommand)
{
	//empty command
	if (!upCommand)
	{
		std::cerr << "Invalid command!\n";
		return false;
	}

	//controller dont exist
	if (key.first + 1 > m_Controllers.size())
	{
		std::cerr << "Can't bind Command to key, specified controller doesn't exist\n";
		return false;
	}

	//assign command
	auto result = m_ControllerCommands.insert(
		std::make_pair(
				std::make_pair(key.first, key.second),
				std::make_pair<std::unique_ptr<Command>, bool>(std::move(upCommand), false)
			)
		);

	std::cout << "Binding of command \"" + std::string(typeid(T).name()) + "\" " + (result.second ? "succeeded" : "failed") + "!\n";

	return result.second;
}
