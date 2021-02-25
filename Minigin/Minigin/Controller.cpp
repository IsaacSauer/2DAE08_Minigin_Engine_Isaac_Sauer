#include "MiniginPCH.h"
#include "Controller.h"

#include <iostream>

void Controller::ProcessInput()
{
	RtlSecureZeroMemory(&m_ControllerKeyStroke, sizeof(XINPUT_KEYSTROKE));
	XInputGetKeystroke(id, 0, &m_ControllerKeyStroke);
}

bool Controller::IsDown(ControllerButton button) const
{
	if (m_ControllerKeyStroke.Flags == XINPUT_KEYSTROKE_REPEAT)
		return CheckState(button);
	return false;
}

bool Controller::IsPressed(ControllerButton button) const
{
	if (m_ControllerKeyStroke.Flags == XINPUT_KEYSTROKE_KEYDOWN)
		return CheckState(button);
	return false;
}

bool Controller::IsReleased(ControllerButton button) const
{
	if (m_ControllerKeyStroke.Flags == XINPUT_KEYSTROKE_KEYUP)
		return CheckState(button);
	return false;
}

bool Controller::CheckState(ControllerButton button) const
{
	return m_ControllerKeyStroke.VirtualKey == (int)button;
}

Controller::Button::Button(UINT controllerID, Controller::ControllerButton button, Controller::ButtonState state)
	:m_ControllerID{ controllerID }
	, m_Button{ button }
	, m_State(state)
{
}

Controller::ControllerButton Controller::Button::GetButton() const
{
	return m_Button;
}

Controller::ButtonState Controller::Button::GetState() const
{
	return m_State;
}

UINT Controller::Button::GetControllerID() const
{
	return m_ControllerID;
}

bool Controller::Button::IsDown() const
{
	return m_IsDown;
}

bool Controller::Button::operator<(const Button& rhs) const
{
	return m_ControllerID < rhs.m_ControllerID
	|| m_Button < rhs.m_Button
	|| m_State < rhs.m_State;
}
