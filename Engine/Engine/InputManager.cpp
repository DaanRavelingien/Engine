#include "EnginePCH.h"
#include "InputManager.h"

#ifdef _DEBUG
#include "imgui_impl_sdl.h"
#endif // _DEBUG

InputManager::~InputManager()
{
	for (std::pair<int, ControllerInput> controllerCmd : m_ControllerCommands)
	{
		for (Command* pCommand : controllerCmd.second.downCommands)
		{
			if (pCommand)
			{
				delete pCommand;
				pCommand = nullptr;
			}
		}
		for (Command* pCommand : controllerCmd.second.pressedCommands)
		{
			if (pCommand)
			{
				delete pCommand;
				pCommand = nullptr;
			}
		}
		for (Command* pCommand : controllerCmd.second.upCommands)
		{
			if (pCommand)
			{
				delete pCommand;
				pCommand = nullptr;
			}
		}
	}

	for (std::pair<KeyboardButton, KeyboardInput> keyboardCmd : m_KeyboardCommands)
	{
		for (Command* pCommand : keyboardCmd.second.downCommands)
		{
			if (pCommand)
			{
				delete pCommand;
				pCommand = nullptr;
			}
		}
		for (Command* pCommand : keyboardCmd.second.pressedCommands)
		{
			if (pCommand)
			{
				delete pCommand;
				pCommand = nullptr;
			}
		}
		for (Command* pCommand : keyboardCmd.second.upCommands)
		{
			if (pCommand)
			{
				delete pCommand;
				pCommand = nullptr;
			}
		}
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
	ControllerInput input{ button, player,std::vector<Command*>{},std::vector<Command*>{},std::vector<Command*>{} };

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
			input.downCommands.push_back(pCommand);
			m_ControllerCommands.emplace(int(m_ControllerCommands.size()), input);
			break;
		case ButtonState::Up:
			input.upCommands.push_back(pCommand);
			m_ControllerCommands.emplace(int(m_ControllerCommands.size()), input);
			break;
		case ButtonState::Pressed:
			input.pressedCommands.push_back(pCommand);
			m_ControllerCommands.emplace(int(m_ControllerCommands.size()), input);
			break;
		default:
			break;
		}
	}
	//if it does exist just add the new command to the list
	else
	{
		switch (buttonState)
		{
		case ButtonState::Down:
			//adding the new command to the list
			m_ControllerCommands.at(it->first).downCommands.push_back(pCommand);
			break;
		case ButtonState::Up:
			//adding the new command to the list
			m_ControllerCommands.at(it->first).upCommands.push_back(pCommand);
			break;
		case ButtonState::Pressed:
			//adding the new command to the list
			m_ControllerCommands.at(it->first).pressedCommands.push_back(pCommand);
			break;
		default:
			break;
		}
	}
}

void InputManager::SetCommand(const KeyboardButton& button, ButtonState buttonState, Command* pCommand)
{
	//if the command doesnt exist yet create it
	KeyboardInput input{ std::vector<Command*>{},std::vector<Command*>{},std::vector<Command*>{} };
	if (m_KeyboardCommands.find(button) == m_KeyboardCommands.end())
	{
		switch (buttonState)
		{
		case ButtonState::Down:
			input.downCommands.push_back(pCommand);
			m_KeyboardCommands.emplace(button, input);
			break;
		case ButtonState::Up:
			input.upCommands.push_back(pCommand);
			m_KeyboardCommands.emplace(button, input);
			break;
		case ButtonState::Pressed:
			input.pressedCommands.push_back(pCommand);
			m_KeyboardCommands.emplace(button, input);
			break;
		default:
			break;
		}
	}
	//if it does exist just add the new command to the list
	else
	{
		switch (buttonState)
		{
		case ButtonState::Down:
			//adding the new command to the list
			m_KeyboardCommands.at(button).downCommands.push_back(pCommand);
			break;
		case ButtonState::Up:
			//adding the new command to the list
			m_KeyboardCommands.at(button).upCommands.push_back(pCommand);
			break;
		case ButtonState::Pressed:
			//adding the new command to the list
			m_KeyboardCommands.at(button).pressedCommands.push_back(pCommand);
			break;
		default:
			break;
		}
	}
}

void InputManager::RemoveCommands(const ControllerButton& button, ButtonState buttonState, Controller player)
{
	auto it = std::find_if(m_ControllerCommands.begin(), m_ControllerCommands.end(), [player, button]
	(const std::pair<int, ControllerInput>& input)
		{
			if (input.second.player == player && button == input.second.button)
				return true;
			return false;
		});

	if (it == m_ControllerCommands.end())
		return;

	switch (buttonState)
	{
	case ButtonState::Down:
		for (Command* pCommand : m_ControllerCommands.at(it->first).downCommands)
		{
			if (pCommand)
			{
				delete pCommand;
				pCommand = nullptr;
			}
		}
		m_ControllerCommands.at(it->first).downCommands.clear();
		m_ControllerCommands.erase(it->first);
		break;
	case ButtonState::Up:
		for (Command* pCommand : m_ControllerCommands.at(it->first).upCommands)
		{
			if (pCommand)
			{
				delete pCommand;
				pCommand = nullptr;
			}
		}
		m_ControllerCommands.at(it->first).upCommands.clear();
		m_ControllerCommands.erase(it->first);
		break;
	case ButtonState::Pressed:
		for (Command* pCommand : m_ControllerCommands.at(it->first).pressedCommands)
		{
			if (pCommand)
			{
				delete pCommand;
				pCommand = nullptr;
			}
		}
		m_ControllerCommands.at(it->first).pressedCommands.clear();
		m_ControllerCommands.erase(it->first);
		break;
	default:
		break;
	}
}

void InputManager::RemoveCommands(const KeyboardButton& button, ButtonState buttonState)
{
	//checking if the button exists
	auto it = m_KeyboardCommands.find(button);
	
	if (it == m_KeyboardCommands.end())
		return;

	switch (buttonState)
	{
	case ButtonState::Down:
		for (Command* pCommand : m_KeyboardCommands.at(button).downCommands)
		{
			if (pCommand)
			{
				delete pCommand;
				pCommand = nullptr;
			}
		}
		m_KeyboardCommands.at(button).downCommands.clear();
		m_KeyboardCommands.erase(button);
		break;
	case ButtonState::Up:
		for (Command* pCommand : m_KeyboardCommands.at(button).upCommands)
		{
			if (pCommand)
			{
				delete pCommand;
				pCommand = nullptr;
			}
		}
		m_KeyboardCommands.at(button).upCommands.clear();
		m_KeyboardCommands.erase(button);
		break;
	case ButtonState::Pressed:
		for (Command* pCommand : m_KeyboardCommands.at(button).pressedCommands)
		{
			if (pCommand)
			{
				delete pCommand;
				pCommand = nullptr;
			}
		}
		m_KeyboardCommands.at(button).pressedCommands.clear();
		m_KeyboardCommands.erase(button);
		break;
	default:
		break;
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
				for (Command* pCommand : m_ControllerCommands.at(input.first).pressedCommands)
				{
					if (pCommand != nullptr && pCommand->IsEnabled())
						pCommand->Execute();
				}
			}
		}
		//if the button is released execute the commands associated with it
		if (m_Keystrokes.Flags == XINPUT_KEYSTROKE_KEYUP)
		{
			if (IsPressed(input.second.button))
			{
				for (Command* pCommand : m_ControllerCommands.at(input.first).upCommands)
				{
					if (pCommand != nullptr && pCommand->IsEnabled())
						pCommand->Execute();
				}
			}
		}
		//if the button is pressed down execute the commands associated with it
		if (m_Keystrokes.Flags == XINPUT_KEYSTROKE_KEYDOWN)
		{
			if (IsPressed(input.second.button))
			{
				for (Command* pCommand : m_ControllerCommands.at(input.first).downCommands)
				{
					if (pCommand != nullptr && pCommand->IsEnabled())
						pCommand->Execute();
				}
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
		for (Command* pCommand : it->second.pressedCommands)
		{
			if (pCommand != nullptr && pCommand->IsEnabled())
				pCommand->Execute();
		}
	}
	if (m_SDLEvent.type == SDL_KEYUP)
	{
		for (Command* pCommand : it->second.upCommands)
		{
			if (pCommand != nullptr && pCommand->IsEnabled())
				pCommand->Execute();
		}
	}
}

