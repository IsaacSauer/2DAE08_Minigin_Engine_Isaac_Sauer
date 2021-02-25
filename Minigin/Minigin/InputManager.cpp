#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>


bool dae::InputManager::ProcessInput()
{
	// todo: read the input
	for (auto& controller : m_Controllers)
	{
		controller->ProcessInput();
	}

	//Handle Input
	for (auto& command : m_ControllerCommands)
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

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
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

UINT dae::InputManager::AddController()
{
	UINT size = UINT(m_Controllers.size());
	if (size < 4)
	{
		m_Controllers.push_back(std::make_unique<Controller>(Controller{ size }));
		return size;
	}

	std::cerr << "Max controllers reached! (4)\n";
	return 0;
}

dae::InputManager::ControllerKeyType dae::InputManager::ControllerKey(UINT id, Controller::ControllerButton button,
	Controller::ButtonState state)
{
	return std::make_pair(id, std::make_pair(button, state));
}