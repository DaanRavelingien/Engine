#pragma once
#include <XInput.h>
#include "Command.h"
#include <map>

enum class ControllerButton
{
	ButtonCross = VK_PAD_A,
	ButtonA = VK_PAD_A,
	ButtonCircle = VK_PAD_B,
	ButtonB = VK_PAD_B,
	ButtonSquare = VK_PAD_X,
	ButtonX = VK_PAD_X,
	ButtonTriangle = VK_PAD_Y,
	ButtonY = VK_PAD_Y,
	DpadUp = VK_PAD_DPAD_UP,
	DpadDown = VK_PAD_DPAD_DOWN,
	DpadLeft = VK_PAD_DPAD_LEFT,
	DpadRight = VK_PAD_DPAD_RIGHT,
	ButtonStart = VK_PAD_START,
	ButtonBack = VK_PAD_BACK,
	LeftBumper = VK_PAD_LSHOULDER,
	LeftThumb = VK_PAD_LTHUMB_PRESS,
	RightBumper = VK_PAD_RSHOULDER,
	RightThumb = VK_PAD_RTHUMB_PRESS,
	StartButton = VK_PAD_START,
	BackButton = VK_PAD_BACK,
	NR_OF_BUTTONS = 19
};

enum class KeyboardButton
{
	//numbers
	NR0 = SDL_SCANCODE_0,
	NR1 = SDL_SCANCODE_1,
	NR2 = SDL_SCANCODE_2,
	NR3 = SDL_SCANCODE_3,
	NR4 = SDL_SCANCODE_4,
	NR5 = SDL_SCANCODE_4,
	NR6 = SDL_SCANCODE_6,
	NR7 = SDL_SCANCODE_7,
	NR8 = SDL_SCANCODE_8,
	NR9 = SDL_SCANCODE_9,

	//Letters
	A = SDL_SCANCODE_A,
	B = SDL_SCANCODE_B,
	C = SDL_SCANCODE_C,
	D = SDL_SCANCODE_D,
	E = SDL_SCANCODE_E,
	F = SDL_SCANCODE_F,
	G = SDL_SCANCODE_G,
	H = SDL_SCANCODE_H,
	I = SDL_SCANCODE_I,
	J = SDL_SCANCODE_J,
	K = SDL_SCANCODE_K,
	L = SDL_SCANCODE_L,
	M = SDL_SCANCODE_M,
	N = SDL_SCANCODE_N,
	O = SDL_SCANCODE_O,
	P = SDL_SCANCODE_P,
	Q = SDL_SCANCODE_Q,
	R = SDL_SCANCODE_R,
	S = SDL_SCANCODE_S,
	T = SDL_SCANCODE_T,
	U = SDL_SCANCODE_U,
	V = SDL_SCANCODE_V,
	W = SDL_SCANCODE_W,
	X = SDL_SCANCODE_X,
	Y = SDL_SCANCODE_Y,
	Z = SDL_SCANCODE_Z,
	//miscKeys
	SPACE = SDL_SCANCODE_SPACE,
	LSHIFT = SDL_SCANCODE_LSHIFT,
	RSHIFT = SDL_SCANCODE_RSHIFT,
	UP = SDL_SCANCODE_UP,
	DOWN = SDL_SCANCODE_DOWN,
	LEFT = SDL_SCANCODE_LEFT,
	RIGHT = SDL_SCANCODE_RIGHT,
	LCTRL = SDL_SCANCODE_LCTRL,
	RCTRL = SDL_SCANCODE_RCTRL,
	ESC = SDL_SCANCODE_ESCAPE,
	TAB = SDL_SCANCODE_TAB,
	ENTER = SDL_SCANCODE_RETURN
};

enum class ButtonState
{
	Down, Up, Pressed
};

enum class Controller
{
	Controller_1 = 0, Controller_2 = 1
};

class InputManager final
{
public:
	InputManager() = default;
	~InputManager();
	bool ProcessInput();

	bool IsPressed(const ControllerButton& button) const;
	bool IsPressed(const KeyboardButton & button) const;
	void SetCommand(const ControllerButton & button, ButtonState buttonState, Command * pCommand, Controller player);
	//keyboard down commands do not work at the moment
	void SetCommand(const KeyboardButton & button, ButtonState buttonState, Command * pCommand);
	
	void SetControllerAmount(int amount) { m_ControllerAmount = amount; };
	void QuitGame() { m_Quit = true; };

private:
	//only supports one command per button per action
	struct KeyboardInput
	{
		std::vector<Command*> upCommands{};
		std::vector<Command*> pressedCommands{};
		std::vector<Command*> downCommands{};
	};

	struct ControllerInput
	{
		ControllerButton button{};
		Controller player{ Controller::Controller_1 };
		std::vector<Command*> upCommands{};
		std::vector<Command*> pressedCommands{};
		std::vector<Command*> downCommands{};
	};

	int m_ControllerAmount{ 1 };
	bool m_Quit{ false };

	XINPUT_KEYSTROKE m_Keystrokes{};
	SDL_Event m_SDLEvent{};
	std::map<int, ControllerInput> m_ControllerCommands{};
	std::map<KeyboardButton, KeyboardInput> m_KeyboardCommands{};

	void HandleControllerInput(Controller player);
	void HandleKeyboardInput();
};


