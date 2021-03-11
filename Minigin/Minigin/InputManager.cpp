#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>


bool dae::InputManager::ProcessInput()
{
	//Retreive SDLInput
	m_SDLEvents.clear();
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		m_SDLEvents.push_back(e);
	}

	// ProcessControllers
	for (auto& controller : m_Controllers)
	{
		controller->ProcessInput();
	}

	//Handle Controller Commands
	for (auto& command : m_ControllerInputCommands)
	{
		switch (command.first.second.second)
		{
		case Controller::ButtonState::REPEAT:
			if (IsButtonReleased(command.first.second.first, command.first.first))
				command.second.second = false;
			if (IsButtonPressed(command.first.second.first, command.first.first))
				command.second.second = true;
			if(command.second.second)
				command.second.first->Execute();
			break;
		case Controller::ButtonState::KEYDOWN:
			if (IsButtonPressed(command.first.second.first, command.first.first))
			{
				command.second.second = true;
				command.second.first->Execute();
			}
			break;
		case Controller::ButtonState::KEYUP:
			if (IsButtonReleased(command.first.second.first, command.first.first))
			{
				command.second.second = false;
				command.second.first->Execute();
			}
			break;
		}
	}

	//Handle keyboard Commands
	for(auto& command : m_SDLInputCommands)
	{
		if(command.first.second == KEYDOWN)
		{
			if (CheckSDLEvent(command.first.first, KEYPRESSED))
				command.second.second = true;
			if (CheckSDLEvent(command.first.first, KEYRELEASED))
				command.second.second = false;
			if (command.second.second)
				command.second.first->Execute();
		}
		else if (CheckSDLEvent(command.first.first, command.first.second))
			command.second.first->Execute();
	}
	return true;
}

bool dae::InputManager::IsButtonDown(Controller::ControllerButton button, UINT controllerId) const
{
	//controller dont exist
	if (controllerId + 1 > m_Controllers.size())
	{
		std::cerr << "Controller ID is inValid!\n";
		return false;
	}

	// todo done: return whether the given button is pressed or not.
	
	return m_Controllers.at(controllerId)->IsDown(button);
}

bool dae::InputManager::IsButtonPressed(Controller::ControllerButton button, UINT controllerId) const
{
	//controller dont exist
	if (controllerId + 1 > m_Controllers.size())
	{
		std::cerr << "Controller ID is inValid!\n";
		return false;
	}

	// todo done: return whether the given button is pressed or not.
	return m_Controllers.at(controllerId)->IsPressed(button);
}

bool dae::InputManager::IsButtonReleased(Controller::ControllerButton button, UINT controllerId) const
{
	//controller dont exist
	if (controllerId + 1 > m_Controllers.size())
	{
		std::cerr << "Controller ID is inValid!\n";
		return false;
	}

	// todo done: return whether the given button is pressed or not.
	return m_Controllers.at(controllerId)->IsReleased(button);
}

bool dae::InputManager::CheckSDLEvent(SDL_Keycode key, SDLEvent type) const
{
	for(const SDL_Event& event : m_SDLEvents)
	{
		switch (type)
		{
		//Check if requested quit
		case QUIT:
			if (event.type == static_cast<Uint32>(type))
				return true;
			break;
		case KEYDOWN:
			if (event.type == SDL_KEYDOWN)
				return true;
		default:
			if (event.type == static_cast<Uint32>(type)
				&& event.key.keysym.sym == key
				&& event.key.repeat == 0)
			{
				return true;
			}
		}
	}
	return false;
}

UINT dae::InputManager::AddController()
{
	//MUTEX
	std::lock_guard<std::mutex> guard(m_ControllersMutex);


	UINT size = UINT(m_Controllers.size());
	if (size < 4)
	{
		m_Controllers.push_back(std::make_unique<Controller>(Controller{ size }));
		return size;
	}

	std::cerr << "Max controllers reached! (4)\n";
	return 0;
}

dae::InputManager::ControllerInputEvent dae::InputManager::ControllerKey(UINT id, Controller::ControllerButton button,
	Controller::ButtonState state)
{
	return std::make_pair(id, std::make_pair(button, state));
}