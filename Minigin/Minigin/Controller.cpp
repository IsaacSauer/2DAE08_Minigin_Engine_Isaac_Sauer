#include "MiniginPCH.h"
#include "Controller.h"

#include <iostream>

void Controller::ProcessInput()
{
	RtlSecureZeroMemory(&m_ControllerInputState, sizeof(XINPUT_STATE));
	XInputGetState(id, &m_ControllerInputState);

	RtlSecureZeroMemory(&m_ControllerKeyStroke, sizeof(XINPUT_KEYSTROKE));
	XInputGetKeystroke(id, 0, &m_ControllerKeyStroke);
}

bool Controller::IsDown(ControllerButton button) const
{
	switch (button)
	{
	case ControllerButton::PAD_A:
		return m_ControllerInputState.Gamepad.wButtons & XINPUT_GAMEPAD_A;
	case ControllerButton::PAD_B:
		return m_ControllerInputState.Gamepad.wButtons & XINPUT_GAMEPAD_B;
	case ControllerButton::PAD_X:
		return m_ControllerInputState.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	case ControllerButton::PAD_Y:
		return m_ControllerInputState.Gamepad.wButtons & XINPUT_GAMEPAD_X;
	case ControllerButton::PAD_RSHOULDER:
		return m_ControllerInputState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER;
	case ControllerButton::PAD_LSHOULDER:
		return m_ControllerInputState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER;
	case ControllerButton::PAD_DPAD_UP:
		return m_ControllerInputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
	case ControllerButton::PAD_DPAD_DOWN:
		return m_ControllerInputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
	case ControllerButton::PAD_DPAD_LEFT:
		return m_ControllerInputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
	case ControllerButton::PAD_DPAD_RIGHT:
		return m_ControllerInputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
	case ControllerButton::PAD_START:
		return m_ControllerInputState.Gamepad.wButtons & XINPUT_GAMEPAD_START;
	case ControllerButton::PAD_BACK:
		return m_ControllerInputState.Gamepad.wButtons & XINPUT_GAMEPAD_BACK;
	case ControllerButton::PAD_LTHUMB_PRESS:
		return m_ControllerInputState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB;
	case ControllerButton::PAD_RTHUMB_PRESS:
		return m_ControllerInputState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB;
	}
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