#include "EnginePCH.h"
#include "MenuInputComp.h"
#include "InputManager.h"
#include "MenuComp.h"
#include "SceneManager.h"
#include "Scene.h"

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
	InputManager::GetInstance().SetCommand(KeyboardButton::ENTER, ButtonState::Up, new MenuSelectCmd{ m_pGameObj,this });
}

void MenuUpCmd::Execute()
{
	if(SceneManager::GetInstance().GetActiveScene()->GetName().compare(GetGameObject()->GetScene()->GetName()) == 0)
		GetGameObject()->GetComponent<MenuComp>()->SelectPrev();
}

void MenuDownCmd::Execute()
{
	if (SceneManager::GetInstance().GetActiveScene()->GetName().compare(GetGameObject()->GetScene()->GetName()) == 0)
		GetGameObject()->GetComponent<MenuComp>()->SelectNext();
}

void MenuSelectCmd::Execute()
{
	if (SceneManager::GetInstance().GetActiveScene()->GetName().compare(GetGameObject()->GetScene()->GetName()) == 0)
		GetGameObject()->GetComponent<MenuComp>()->Select();
}
