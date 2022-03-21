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
	m_pGameObj->GetScene()->GetInputManager()->SetCommand(ControllerButton::DpadDown, ButtonState::Up, new MenuDownCmd{ m_pGameObj,this }, Controller::Controller_1);
	m_pGameObj->GetScene()->GetInputManager()->SetCommand(ControllerButton::DpadUp, ButtonState::Up, new MenuUpCmd{ m_pGameObj,this }, Controller::Controller_1);
	m_pGameObj->GetScene()->GetInputManager()->SetCommand(ControllerButton::ButtonA, ButtonState::Up, new MenuSelectCmd{ m_pGameObj,this }, Controller::Controller_1);

	//keyboard input
	m_pGameObj->GetScene()->GetInputManager()->SetCommand(KeyboardButton::DOWN, ButtonState::Up, new MenuDownCmd{ m_pGameObj,this });
	m_pGameObj->GetScene()->GetInputManager()->SetCommand(KeyboardButton::UP, ButtonState::Up, new MenuUpCmd{ m_pGameObj,this });
	m_pGameObj->GetScene()->GetInputManager()->SetCommand(KeyboardButton::ENTER, ButtonState::Up, new MenuSelectCmd{ m_pGameObj,this });
}

void MenuUpCmd::Execute()
{
		GetGameObject()->GetComponent<MenuComp>()->SelectPrev();
}

void MenuDownCmd::Execute()
{
		GetGameObject()->GetComponent<MenuComp>()->SelectNext();
}

void MenuSelectCmd::Execute()
{
		GetGameObject()->GetComponent<MenuComp>()->Select();
}
