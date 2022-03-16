#include "EnginePCH.h"
#include "DamageInpComp.h"
#include "InputManager.h"

//component includes
#include "HealthComp.h"

DamageInpComp::DamageInpComp()
	: Component(typeid(this).name())
{
}

void DamageInpComp::Initialize()
{
	std::cout << "\n\nTo damage player press:\tD\nTo heal player press:\tH\n";

	CreateCommands();
}

void DamageInpComp::CreateCommands()
{
	InputManager::GetInstance().SetCommand(KeyboardButton::D, ButtonState::Up, new Damage{ m_pGameObj });
	InputManager::GetInstance().SetCommand(KeyboardButton::H, ButtonState::Up, new Heal{ m_pGameObj });
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
