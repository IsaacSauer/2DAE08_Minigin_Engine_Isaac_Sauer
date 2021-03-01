#pragma once
#include <windows.h>
#include <Xinput.h>

class Controller final
{
public:
	enum class ControllerButton
	{
		PAD_A = 0x5800,
		PAD_B = 0x5801,
		PAD_X = 0x5802,
		PAD_Y = 0x5803,
		PAD_RSHOULDER = 0x5804,
		PAD_LSHOULDER = 0x5805,
		PAD_LTRIGGER = 0x5806,
		PAD_RTRIGGER = 0x5807,
		PAD_DPAD_UP = 0x5810,
		PAD_DPAD_DOWN = 0x5811,
		PAD_DPAD_LEFT = 0x5812,
		PAD_DPAD_RIGHT = 0x5813,
		PAD_START = 0x5814,
		PAD_BACK = 0x5815,
		PAD_LTHUMB_PRESS = 0x5816,
		PAD_RTHUMB_PRESS = 0x5817,
		PAD_LTHUMB_UP = 0x5820,
		PAD_LTHUMB_DOWN = 0x5821,
		PAD_LTHUMB_RIGHT = 0x5822,
		PAD_LTHUMB_LEFT = 0x5823,
		PAD_LTHUMB_UPLEFT = 0x5824,
		PAD_LTHUMB_UPRIGHT = 0x5825,
		PAD_LTHUMB_DOWNRIGHT = 0x5826,
		PAD_LTHUMB_DOWNLEFT = 0x5827,
		PAD_RTHUMB_UP = 0x5830,
		PAD_RTHUMB_DOWN = 0x5831,
		PAD_RTHUMB_RIGHT = 0x5832,
		PAD_RTHUMB_LEFT = 0x5833,
		PAD_RTHUMB_UPLEFT = 0x5834,
		PAD_RTHUMB_UPRIGHT = 0x5835,
		PAD_RTHUMB_DOWNRIGHT = 0x5836,
		PAD_RTHUMB_DOWNLEFT = 0x5837,
	};
	enum class ButtonState
	{
		KEYDOWN,
		KEYUP,
		REPEAT,
	};

public:
	explicit Controller(UINT id) :id{ id } {}

	void ProcessInput();
	bool IsDown(ControllerButton button) const;
	bool IsPressed(ControllerButton button) const;
	bool IsReleased(ControllerButton button) const;
private:
	bool CheckState(ControllerButton button) const;

	XINPUT_KEYSTROKE m_ControllerKeyStroke{};
	UINT id{};
};
