#include "EnginePCH.h"
#include "MenuInputComp.h"
#include "InputManager.h"
#include "MainMenuManagerComp.h"

MenuInputComp::MenuInputComp()
	:Component{typeid(this).name()}
{
}

void MenuInputComp::Initialize()
{
	//controller input
	InputManager::GetInstance().SetCommand(ControllerButton::DpadDown, ButtonState::Up, new MenuDownCmd{ m_pGameObj,this }, Controller::Controller_1);
	InputManager::GetInstance().SetCommand(ControllerButton::DpadUp, ButtonState::Up, new MenuUpCmd{ m_pGameObj,this }, Controller::Controller_1);
	InputManager::GetInstance().SetCommand(ControllerButton::ButtonA, ButtonState::Up, new MenuSelectCmd{ m_pGameObj,this }, Controller::Controller_1);
	
	//keyboard input
	InputManager::GetInstance().SetCommand(KeyboardButton::DOWN, ButtonState::Up, new MenuDownCmd{ m_pGameObj,this });
	InputManager::GetInstance().SetCommand(KeyboardButton::UP, ButtonState::Up, new MenuUpCmd{ m_pGameObj,this });
	InputManager::GetInstance().SetCommand(KeyboardButton::SPACE, ButtonState::Up, new MenuSelectCmd{ m_pGameObj,this });
}

void MenuUpCmd::Execute()
{
	GetGameObject()->GetComponent<MainMenuManagerComp>()->SelectPrev();
}

void MenuDownCmd::Execute()
{
	GetGameObject()->GetComponent<MainMenuManagerComp>()->SelectNext();
}

void MenuSelectCmd::Execute()
{
	GetGameObject()->GetComponent<MainMenuManagerComp>()->Select();
}
