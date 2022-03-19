#include "EnginePCH.h"
#include "InputManager.h"

#ifdef _DEBUG
#include "imgui_impl_sdl.h"
#endif // _DEBUG

InputManager::~InputManager()
{
	for (std::pair<int, ControllerInput> controllerCmd : m_ControllerCommands)
	{
		delete controllerCmd.second.downCommand;
		controllerCmd.second.downCommand = nullptr;
		delete controllerCmd.second.upCommand;
		controllerCmd.second.upCommand = nullptr;
		delete controllerCmd.second.pressedCommand;
		controllerCmd.second.pressedCommand = nullptr;
	}

	for (std::pair<KeyboardButton, KeyboardInput> keyboardCmd : m_KeyboardCommands)
	{
		delete keyboardCmd.second.downCommand;
		keyboardCmd.second.downCommand = nullptr;
		delete keyboardCmd.second.upCommand;
		keyboardCmd.second.upCommand = nullptr;
		delete keyboardCmd.second.pressedCommand;
		keyboardCmd.second.pressedCommand = nullptr;
	}
}

bool InputManager::ProcessInput()
{
	//check if we need to quit the game
	if (m_Quit)
		return false;

	//controller input
	//supports upto 2 controllers
	for (int i{}; i < m_ControllerAmount; i++)
	{
		DWORD result{ XInputGetKeystroke((DWORD)i, 0, &m_Keystrokes) };
		if (result == ERROR_SUCCESS)
			HandleControllerInput((Controller)i);
	}

	//keyboard / mouse input
	while (SDL_PollEvent(&m_SDLEvent))
	{
#ifdef _DEBUG
		//sending events to the imgui so we can interact with it
		ImGui_ImplSDL2_ProcessEvent(&m_SDLEvent);
#endif // _DEBUG

		if (m_SDLEvent.type == SDL_QUIT)
		{
			//quiting the game when clicked on the cross of the window
			return false;
		}
		if (m_SDLEvent.type == SDL_KEYDOWN || m_SDLEvent.type == SDL_KEYUP)
		{
			//only handel keyboard input if a key is pressed
			HandleKeyboardInput();
		}
		if (m_SDLEvent.type == SDL_MOUSEBUTTONDOWN)
		{
			//mouse input should come here
		}
	}

	return true;
}

bool InputManager::IsPressed(const ControllerButton& button) const
{
	if ((WORD)button == m_Keystrokes.VirtualKey)
		return true;
	return false;
}

bool InputManager::IsPressed(const KeyboardButton& button) const
{
	if ((SDL_Scancode)button == m_SDLEvent.key.keysym.scancode)
		return true;
	return false;
}

void InputManager::SetCommand(const ControllerButton& button, ButtonState buttonState, Command* pCommand, Controller player = Controller::Controller_1)
{
	//if the input doesnt exist yet create it
	ControllerInput input{ button, player,nullptr,nullptr,nullptr };

	auto it = std::find_if(m_ControllerCommands.begin(), m_ControllerCommands.end(), [player, button]
	(const std::pair<int,ControllerInput>& input) 
		{
			if (input.second.player == player && button == input.second.button)
				return true;
			return false;
		});

	if (it == m_ControllerCommands.end())
	{
		switch (buttonState)
		{
		case ButtonState::Down:
			input.downCommand = pCommand;
			m_ControllerCommands.emplace(int(m_ControllerCommands.size()), input);
			break;
		case ButtonState::Up:
			input.upCommand = pCommand;
			m_ControllerCommands.emplace(int(m_ControllerCommands.size()), input);
			break;
		case ButtonState::Pressed:
			input.pressedCommand = pCommand;
			m_ControllerCommands.emplace(int(m_ControllerCommands.size()), input);
			break;
		default:
			break;
		}
	}
	//if it does exist remove the old command and put the new one in place
	else
	{
		switch (buttonState)
		{
		case ButtonState::Down:
			//removing the old command
			if (m_ControllerCommands.at(it->first).downCommand != nullptr)
				delete m_ControllerCommands.at(it->first).downCommand;
			//setting the new command
			m_ControllerCommands.at(it->first).downCommand = pCommand;
			break;
		case ButtonState::Up:
			//removing the old command
			if (m_ControllerCommands.at(it->first).upCommand != nullptr)
				delete m_ControllerCommands.at(it->first).upCommand;
			//setting the new command
			m_ControllerCommands.at(it->first).upCommand = pCommand;
			break;
		case ButtonState::Pressed:
			//removing the old command
			if (m_ControllerCommands.at(it->first).pressedCommand != nullptr)
				delete m_ControllerCommands.at(it->first).pressedCommand;
			//setting the new command
			m_ControllerCommands.at(it->first).pressedCommand = pCommand;
			break;
		default:
			break;
		}
	}
}

void InputManager::SetCommand(const KeyboardButton& button, ButtonState buttonState, Command* pCommand)
{
	//if the command doesnt exist yet create it
	KeyboardInput input{ nullptr,nullptr,nullptr };
	if (m_KeyboardCommands.find(button) == m_KeyboardCommands.end())
	{
		switch (buttonState)
		{
		case ButtonState::Down:
			input.downCommand = pCommand;
			m_KeyboardCommands.emplace(button, input);
			break;
		case ButtonState::Up:
			input.upCommand = pCommand;
			m_KeyboardCommands.emplace(button, input);
			break;
		case ButtonState::Pressed:
			input.pressedCommand = pCommand;
			m_KeyboardCommands.emplace(button, input);
			break;
		default:
			break;
		}
	}
	//if it does exist remove the old command and put the new one in place
	else
	{
		switch (buttonState)
		{
		case ButtonState::Down:
			//removing the old command
			if (m_KeyboardCommands.at(button).downCommand != nullptr)
				delete m_KeyboardCommands.at(button).downCommand;
			//setting the new command
			m_KeyboardCommands.at(button).downCommand = pCommand;
			break;
		case ButtonState::Up:
			//removing the old command
			if (m_KeyboardCommands.at(button).upCommand != nullptr)
				delete m_KeyboardCommands.at(button).upCommand;
			//setting the new command
			m_KeyboardCommands.at(button).upCommand = pCommand;
			break;
		case ButtonState::Pressed:
			//removing the old command
			if (m_KeyboardCommands.at(button).pressedCommand != nullptr)
				delete m_KeyboardCommands.at(button).pressedCommand;
			//setting the new command
			m_KeyboardCommands.at(button).pressedCommand = pCommand;
			break;
		default:
			break;
		}
	}
}

void InputManager::HandleControllerInput(Controller player)
{
	//going through all the buttons and checking wich ones are pressed
	for (const std::pair<int, ControllerInput>& input : m_ControllerCommands)
	{
		//check if the commands are for the correct user
		if (input.second.player != player)
			continue;

		//if the button is pressed execute the commands associated with it
		if (m_Keystrokes.Flags & XINPUT_KEYSTROKE_REPEAT)
		{
			if (IsPressed(input.second.button))
			{
				if (m_ControllerCommands.at(input.first).pressedCommand != nullptr)
					m_ControllerCommands.at(input.first).pressedCommand->Execute();
			}
		}
		//if the button is released execute the commands associated with it
		if (m_Keystrokes.Flags == XINPUT_KEYSTROKE_KEYUP)
		{
			if (IsPressed(input.second.button))
			{
				if (m_ControllerCommands.at(input.first).upCommand != nullptr)
					m_ControllerCommands.at(input.first).upCommand->Execute();
			}
		}
		//if the button is pressed down execute the commands associated with it
		if (m_Keystrokes.Flags == XINPUT_KEYSTROKE_KEYDOWN)
		{
			if (IsPressed(input.second.button))
			{
				if (m_ControllerCommands.at(input.first).downCommand != nullptr)
					m_ControllerCommands.at(input.first).downCommand->Execute();
			}
		}
	}
}

void InputManager::HandleKeyboardInput()
{
	//for keyboard input we only need to check the current button that is pressed and not loop over all of them
	//we do the looping in the proces input fucntion
	auto it = m_KeyboardCommands.find((KeyboardButton)m_SDLEvent.key.keysym.scancode);
	//check if the key is in the map
	if (it == m_KeyboardCommands.end())
		return;

	//TODO: make the down command work as well withs some kind of flag or look a bit more into sdl
	if (m_SDLEvent.type == SDL_KEYDOWN)
	{
		if (it->second.pressedCommand != nullptr)
			it->second.pressedCommand->Execute();
	}
	if (m_SDLEvent.type == SDL_KEYUP)
	{
		if (it->second.upCommand != nullptr)
			it->second.upCommand->Execute();
	}
}

