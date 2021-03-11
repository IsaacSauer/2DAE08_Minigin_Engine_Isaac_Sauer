#pragma once
#include <map>
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <XInput.h>

#include "Command.h"
#include "Controller.h"
#include "Measure.h"
#include "Singleton.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		enum SDLEvent
		{
			QUIT = 0x100,				/**< User-requested quit */
			KEYPRESSED = 0x300,			/**< Key pressed */
			KEYRELEASED,				/**< Key released */
			KEYDOWN,
			MOUSEBUTTONDOWN = 0x401,	/**< Mouse button pressed */
			MOUSEBUTTONUP,				/**< Mouse button released */
		};

		using CommandState = std::pair<std::unique_ptr<Command>, bool>;

		using ControllerInputEvent = std::pair<unsigned, std::pair<Controller::ControllerButton, Controller::ButtonState>>;
		using SDLInputEvent = std::pair<SDL_Keycode, SDLEvent>;

		using ControllerCommandsMap = std::map<ControllerInputEvent, CommandState>;
		using SDLCommandsMap = std::map<SDLInputEvent, CommandState>;

		bool ProcessInput();
		bool IsButtonDown(Controller::ControllerButton button, UINT controllerId = 0) const;
		bool IsButtonPressed(Controller::ControllerButton button, UINT controllerId = 0) const;
		bool IsButtonReleased(Controller::ControllerButton button, UINT controllerId = 0) const;

		bool CheckSDLEvent(SDL_Keycode, SDLEvent) const;

		template <typename T>
		bool AddKeyboardCommand(SDLInputEvent key, std::unique_ptr<T> upCommand);
		template <typename T>
		bool AddControllerCommand(ControllerInputEvent key, std::unique_ptr<T> upCommand);
		UINT AddController();

		static ControllerInputEvent ControllerKey(UINT id, Controller::ControllerButton button,
			Controller::ButtonState state = Controller::ButtonState::REPEAT);
	private:
		ControllerCommandsMap m_ControllerInputCommands{};
		SDLCommandsMap m_SDLInputCommands{};

		std::vector<SDL_Event> m_SDLEvents;
		std::vector<std::unique_ptr<Controller>> m_Controllers{};

		//MUTEXES
		std::mutex m_ControllerCommandsMutex;
		std::mutex m_SDLCommandsMutex;
		std::mutex m_ControllersMutex;
	};

	template <typename commandName>
	inline std::unique_ptr<commandName> CreateCommand()
	{
		return std::move(std::make_unique<commandName>(commandName{}));
	}
	template <typename commandName>
	inline std::unique_ptr<commandName> CreateCommand(const std::shared_ptr<GameObject>& go)
	{
		return std::move(std::make_unique<commandName>(go));
	}

	//Macros
#define INPUTMANAGER dae::InputManager::GetInstance()
}

template <typename T>
bool dae::InputManager::AddKeyboardCommand(SDLInputEvent key, std::unique_ptr<T> upCommand)
{
	//empty command
	if (!upCommand)
	{
		std::cerr << "Invalid command!\n";
		return false;
	}

	//MUTEX
	std::lock_guard<std::mutex> guard(m_SDLCommandsMutex);
	START_MEASUREMENT();

	//assign command
	auto result = m_SDLInputCommands.insert(
		std::make_pair(key, std::make_pair<std::unique_ptr<Command>, bool>(std::move(upCommand), false)));

	std::cout << "Binding of command \"" + std::string(typeid(T).name()) + "\" " + (result.second ? "succeeded" : "failed") + "!\n";

	return result.second;
}

template<typename T>
inline bool dae::InputManager::AddControllerCommand(ControllerInputEvent key, std::unique_ptr<T> upCommand)
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

	//MUTEX
	std::lock_guard<std::mutex> guard(m_ControllerCommandsMutex);
	START_MEASUREMENT();

	//assign command
	auto result = m_ControllerInputCommands.insert(
		std::make_pair(key, std::make_pair<std::unique_ptr<Command>, bool>(std::move(upCommand), false)));

	std::cout << "Binding of command \"" + std::string(typeid(T).name()) + "\" " + (result.second ? "succeeded" : "failed") + "!\n";

	return result.second;
}
