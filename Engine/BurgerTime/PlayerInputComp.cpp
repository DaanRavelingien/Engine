#include "EnginePCH.h"
#include "PlayerInputComp.h"
#include "Scene.h"
#include "InputManager.h"

//component includes
#include "EntityMoveComp.h"

PlayerInputComp::PlayerInputComp()
	:Component{typeid(this).name()}
{
}

void PlayerInputComp::Initialize()
{
	//getting the entity move component
	m_pEntityMoveComp = m_pGameObj->GetComponent<EntityMoveComp>();

	//creating input 
	//==============

	//controller input
	//start movements
	//pressed commands
	m_pGameObj->GetScene()->GetInputManager()->SetCommand(ControllerButton::DpadUp, ButtonState::Pressed,
		new PlayerStartMoveUpCmd{ m_pGameObj }, Controller::Controller_1);
	m_pGameObj->GetScene()->GetInputManager()->SetCommand(ControllerButton::DpadDown, ButtonState::Pressed,
		new PlayerStartMoveDownCmd{ m_pGameObj }, Controller::Controller_1);
	m_pGameObj->GetScene()->GetInputManager()->SetCommand(ControllerButton::DpadLeft, ButtonState::Pressed,
		new PlayerStartMoveLeftCmd{ m_pGameObj }, Controller::Controller_1);
	m_pGameObj->GetScene()->GetInputManager()->SetCommand(ControllerButton::DpadRight, ButtonState::Pressed,
		new PlayerStartMoveRightCmd{ m_pGameObj }, Controller::Controller_1);
	//down commands
	m_pGameObj->GetScene()->GetInputManager()->SetCommand(ControllerButton::DpadUp, ButtonState::Down,
		new PlayerStartMoveUpCmd{ m_pGameObj }, Controller::Controller_1);
	m_pGameObj->GetScene()->GetInputManager()->SetCommand(ControllerButton::DpadDown, ButtonState::Down,
		new PlayerStartMoveDownCmd{ m_pGameObj }, Controller::Controller_1);
	m_pGameObj->GetScene()->GetInputManager()->SetCommand(ControllerButton::DpadLeft, ButtonState::Down,
		new PlayerStartMoveLeftCmd{ m_pGameObj }, Controller::Controller_1);
	m_pGameObj->GetScene()->GetInputManager()->SetCommand(ControllerButton::DpadRight, ButtonState::Down,
		new PlayerStartMoveRightCmd{ m_pGameObj }, Controller::Controller_1);

	//stop movement commands
	m_pGameObj->GetScene()->GetInputManager()->SetCommand(ControllerButton::DpadUp, ButtonState::Up,
		new PlayerStopMoveCmd{ m_pGameObj }, Controller::Controller_1);
	m_pGameObj->GetScene()->GetInputManager()->SetCommand(ControllerButton::DpadDown, ButtonState::Up,
		new PlayerStopMoveCmd{ m_pGameObj }, Controller::Controller_1);
	m_pGameObj->GetScene()->GetInputManager()->SetCommand(ControllerButton::DpadLeft, ButtonState::Up,
		new PlayerStopMoveCmd{ m_pGameObj }, Controller::Controller_1);
	m_pGameObj->GetScene()->GetInputManager()->SetCommand(ControllerButton::DpadRight, ButtonState::Up,
		new PlayerStopMoveCmd{ m_pGameObj }, Controller::Controller_1);

	//keyboard input
	//start movements
	//pressed commands
	m_pGameObj->GetScene()->GetInputManager()->SetCommand(KeyboardButton::W, ButtonState::Pressed,
		new PlayerStartMoveUpCmd{ m_pGameObj });
	m_pGameObj->GetScene()->GetInputManager()->SetCommand(KeyboardButton::S, ButtonState::Pressed,
		new PlayerStartMoveDownCmd{ m_pGameObj });
	m_pGameObj->GetScene()->GetInputManager()->SetCommand(KeyboardButton::A, ButtonState::Pressed,
		new PlayerStartMoveLeftCmd{ m_pGameObj });
	m_pGameObj->GetScene()->GetInputManager()->SetCommand(KeyboardButton::D, ButtonState::Pressed,
		new PlayerStartMoveRightCmd{ m_pGameObj });

	//down commands
	m_pGameObj->GetScene()->GetInputManager()->SetCommand(KeyboardButton::W, ButtonState::Down,
		new PlayerStartMoveUpCmd{ m_pGameObj });
	m_pGameObj->GetScene()->GetInputManager()->SetCommand(KeyboardButton::S, ButtonState::Down,
		new PlayerStartMoveDownCmd{ m_pGameObj });
	m_pGameObj->GetScene()->GetInputManager()->SetCommand(KeyboardButton::A, ButtonState::Down,
		new PlayerStartMoveLeftCmd{ m_pGameObj });
	m_pGameObj->GetScene()->GetInputManager()->SetCommand(KeyboardButton::D, ButtonState::Down,
		new PlayerStartMoveRightCmd{ m_pGameObj });

	//stop movement commands
	m_pGameObj->GetScene()->GetInputManager()->SetCommand(KeyboardButton::W, ButtonState::Up,
		new PlayerStopMoveCmd{ m_pGameObj });
	m_pGameObj->GetScene()->GetInputManager()->SetCommand(KeyboardButton::S, ButtonState::Up,
		new PlayerStopMoveCmd{ m_pGameObj });
	m_pGameObj->GetScene()->GetInputManager()->SetCommand(KeyboardButton::A, ButtonState::Up,
		new PlayerStopMoveCmd{ m_pGameObj });
	m_pGameObj->GetScene()->GetInputManager()->SetCommand(KeyboardButton::D, ButtonState::Up,
		new PlayerStopMoveCmd{ m_pGameObj });
}

void PlayerInputComp::Update()
{
	switch (m_MoveDirection)
	{
	case PlayerInputComp::Direction::Up:
		m_pEntityMoveComp->MoveUp();
		break;
	case PlayerInputComp::Direction::Down:
		m_pEntityMoveComp->MoveDown();
		break;
	case PlayerInputComp::Direction::Left:
		m_pEntityMoveComp->MoveLeft();
		break;
	case PlayerInputComp::Direction::Right:
		m_pEntityMoveComp->MoveRight();
		break;
	case PlayerInputComp::Direction::Stand:
	default:
		break;
	}
}

void PlayerStartMoveUpCmd::Execute()
{
	GetGameObject()->GetComponent<PlayerInputComp>()->SetMoveDirection(PlayerInputComp::Direction::Up);
}

void PlayerStartMoveDownCmd::Execute()
{
	GetGameObject()->GetComponent<PlayerInputComp>()->SetMoveDirection(PlayerInputComp::Direction::Down);
}

void PlayerStartMoveLeftCmd::Execute()
{
	GetGameObject()->GetComponent<PlayerInputComp>()->SetMoveDirection(PlayerInputComp::Direction::Left);
}

void PlayerStartMoveRightCmd::Execute()
{
	GetGameObject()->GetComponent<PlayerInputComp>()->SetMoveDirection(PlayerInputComp::Direction::Right);
}

void PlayerStopMoveCmd::Execute()
{
	GetGameObject()->GetComponent<PlayerInputComp>()->SetMoveDirection(PlayerInputComp::Direction::Stand);
}
