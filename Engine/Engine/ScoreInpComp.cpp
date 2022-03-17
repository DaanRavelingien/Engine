#include "EnginePCH.h"
#include "ScoreInpComp.h"
#include "InputManager.h"
#include "GameObject.h"

ScoreInpComp::ScoreInpComp()
	:Component{typeid(this).name()}
{
}

void ScoreInpComp::Initialize()
{
	std::cout << "\n\nTo kill enemy press:\tK\nTo drop burger press:\tB\n";

	InputManager::GetInstance().SetCommand(KeyboardButton::K, ButtonState::Up, new EnemyDiedCmd{ m_pGameObj,this });
	InputManager::GetInstance().SetCommand(KeyboardButton::B, ButtonState::Up, new BurgerDorpCmd{ m_pGameObj,this });
}

void EnemyDiedCmd::Execute()
{
	GetGameObject()->SendNotification(m_pComp, Event::COMPONENT_ENEMY_DIES);
}

void BurgerDorpCmd::Execute()
{
	GetGameObject()->SendNotification(m_pComp, Event::COMPONENT_BURGER_DROPS);
}
