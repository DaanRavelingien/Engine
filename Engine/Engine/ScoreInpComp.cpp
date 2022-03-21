#include "EnginePCH.h"
#include "ScoreInpComp.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Scene.h"

ScoreInpComp::ScoreInpComp(Controller inpController)
	:Component{typeid(this).name()}
	,m_InpController{ inpController }
{
}

void ScoreInpComp::Initialize()
{
	std::cout << "\n\nController:\nTo kill enemy press:\tA\nTo drop burger press:\tB\n";

	//controller input
	m_pGameObj->GetScene()->GetInputManager()->SetCommand(ControllerButton::ButtonA, ButtonState::Up, new EnemyDiedCmd{ m_pGameObj,this }, m_InpController);
	m_pGameObj->GetScene()->GetInputManager()->SetCommand(ControllerButton::ButtonB, ButtonState::Up, new BurgerDorpCmd{ m_pGameObj,this }, m_InpController);
}

void EnemyDiedCmd::Execute()
{
	GetGameObject()->SendNotification(m_pComp, Event::COMPONENT_ENEMY_DIES);
}

void BurgerDorpCmd::Execute()
{
	GetGameObject()->SendNotification(m_pComp, Event::COMPONENT_BURGER_DROPS);
}
