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
