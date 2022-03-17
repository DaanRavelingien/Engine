#include "EnginePCH.h"
#include "InputManager.h"

#ifdef _DEBUG
#include "imgui_impl_sdl.h"
#endif // _DEBUG

InputManager::~InputManager()
{
	for (std::pair<ControllerButton, Input> controllerCmd : m_ControllerCommands)
	{
		delete controllerCmd.second.downCommand;
		controllerCmd.second.downCommand = nullptr;
		delete controllerCmd.second.upCommand;
		controllerCmd.second.upCommand = nullptr;
		delete controllerCmd.second.pressedCommand;
		controllerCmd.second.pressedCommand = nullptr;
	}

	for (std::pair<KeyboardButton, Input> keyboardCmd : m_KeyboardCommands)
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
	//controller input
	//supports upto 2 controllers
	for (int i{}; i < 2; i++)
	{
		XInputGetKeystroke((DWORD)i, 0, &m_Keystrokes);
		HandleControllerInput((Player)i);
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

void InputManager::SetCommand(const ControllerButton& button, ButtonState buttonState, Command* pCommand, Player player)
{
	//if the input doesnt exist yet create it
	Input input{ player,nullptr,nullptr,nullptr };

	auto it = std::find_if(m_ControllerCommands.begin(), m_ControllerCommands.end(), [player, button]
	(const std::pair<ControllerButton,Input>& input) 
		{
			if (input.second.player == player && button == input.first)
				return true;
			return false;
		});

	if (it == m_ControllerCommands.end())
	{
		switch (buttonState)
		{
		case ButtonState::Down:
			input.downCommand = pCommand;
			m_ControllerCommands.emplace(button, input);
			break;
		case ButtonState::Up:
			input.upCommand = pCommand;
			m_ControllerCommands.emplace(button, input);
			break;
		case ButtonState::Pressed:
			input.pressedCommand = pCommand;
			m_ControllerCommands.emplace(button, input);
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
			if (m_ControllerCommands.at(button).downCommand != nullptr)
				delete m_ControllerCommands.at(button).downCommand;
			//setting the new command
			m_ControllerCommands.at(button).downCommand = pCommand;
			break;
		case ButtonState::Up:
			//removing the old command
			if (m_ControllerCommands.at(button).upCommand != nullptr)
				delete m_ControllerCommands.at(button).upCommand;
			//setting the new command
			m_ControllerCommands.at(button).upCommand = pCommand;
			break;
		case ButtonState::Pressed:
			//removing the old command
			if (m_ControllerCommands.at(button).pressedCommand != nullptr)
				delete m_ControllerCommands.at(button).pressedCommand;
			//setting the new command
			m_ControllerCommands.at(button).pressedCommand = pCommand;
			break;
		default:
			break;
		}
	}
}

void InputManager::SetCommand(const KeyboardButton& button, ButtonState buttonState, Command* pCommand)
{
	//if the command doesnt exist yet create it
	Input input{ Player::Player1,nullptr,nullptr,nullptr };
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

void InputManager::HandleControllerInput(Player player)
{
	//going through all the buttons and checking wich ones are pressed
	for (const std::pair<ControllerButton, Input>& input : m_ControllerCommands)
	{
		//check if the commands are for the correct user
		if (input.second.player != player)
			continue;

		//if the button is pressed execute the commands associated with it
		if (m_Keystrokes.Flags & XINPUT_KEYSTROKE_REPEAT)
		{
			if (IsPressed(input.first))
			{
				if (m_ControllerCommands.at(input.first).pressedCommand != nullptr)
					m_ControllerCommands.at(input.first).pressedCommand->Execute();
			}
		}
		//if the button is released execute the commands associated with it
		if (m_Keystrokes.Flags == XINPUT_KEYSTROKE_KEYUP)
		{
			if (IsPressed(input.first))
			{
				if (m_ControllerCommands.at(input.first).upCommand != nullptr)
					m_ControllerCommands.at(input.first).upCommand->Execute();
			}
		}
		//if the button is pressed down execute the commands associated with it
		if (m_Keystrokes.Flags == XINPUT_KEYSTROKE_KEYDOWN)
		{
			if (IsPressed(input.first))
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

