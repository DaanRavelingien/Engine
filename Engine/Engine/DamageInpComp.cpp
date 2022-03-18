#include "EnginePCH.h"
#include "DamageInpComp.h"
#include "InputManager.h"

//component includes
#include "HealthComp.h"

DamageInpComp::DamageInpComp(Controller inpController)
	: Component(typeid(this).name())
	,m_InpController{ inpController }
{
}

void DamageInpComp::Initialize()
{
	std::cout << "\n\nController:\nTo damage player press:\tX\nTo heal player press:\tY\n";

	InputManager::GetInstance().SetCommand(ControllerButton::ButtonX, ButtonState::Up, new Damage{ m_pGameObj }, m_InpController);
	InputManager::GetInstance().SetCommand(ControllerButton::ButtonY, ButtonState::Up, new Heal{ m_pGameObj }, m_InpController);
}

void Damage::Execute()
{
	HealthComp* pHealthComp{ GetGameObject()->GetComponent<HealthComp>() };

	if (pHealthComp)
	{
		pHealthComp->Damage(1);
	}
}

void Heal::Execute()
{
	HealthComp* pHealthComp{ GetGameObject()->GetComponent<HealthComp>() };

	if (pHealthComp)
	{
		pHealthComp->Heal(1);
	}
}