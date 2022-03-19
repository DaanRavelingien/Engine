#include "EnginePCH.h"
#include "MainMenuManagerComp.h"
#include "GameObject.h"
#include "TextComp.h"
#include "MenuPointerComp.h"
#include "SceneManager.h"

MainMenuManagerComp::MainMenuManagerComp()
	:Component{typeid(this).name()}
{
}

void MainMenuManagerComp::Initialize()
{
	for (GameObject* pObj : m_pGameObj->GetChildren())
	{
		//getting the menu pointer
		if (pObj->GetComponent<MenuPointerComp>())
			m_pMenuPointerComp = pObj->GetComponent<MenuPointerComp>();

		//getting the menu options
		TextComp* pTextComp{ pObj->GetComponent<TextComp>() };

		if (!pTextComp)
			continue;
		
		m_MenuOptions.push_back(pTextComp->GetText());
	}

	m_SelectedMenuOption = m_MenuOptions.front();
}

void MainMenuManagerComp::SelectNext()
{
	if (m_pMenuPointerComp)
	{
		m_pMenuPointerComp->MovePointerDown();
		m_SelectedMenuOption = m_MenuOptions.at(m_pMenuPointerComp->GetPointerPos());
	}
}

void MainMenuManagerComp::SelectPrev()
{
	if (m_pMenuPointerComp)
	{
		m_pMenuPointerComp->MovePointerUp();
		m_SelectedMenuOption = m_MenuOptions.at(m_pMenuPointerComp->GetPointerPos());
	}
}

void MainMenuManagerComp::Select()
{
	if (m_SelectedMenuOption.compare("1 PLAYER"))
		SceneManager::GetInstance().SetActiveScene("BurgerTimeLvl");

	if (m_SelectedMenuOption.compare("2 PLAYERS CO OP"))
		SceneManager::GetInstance().SetActiveScene("BurgerTimeLvl");

	if (m_SelectedMenuOption.compare("2 PLAYERS VERSUS"))
		SceneManager::GetInstance().SetActiveScene("BurgerTimeLvl");

	if (m_SelectedMenuOption.compare("OPTIONS"))
		SceneManager::GetInstance().SetActiveScene("BurgerTimeLvl");

	if (m_SelectedMenuOption.compare("EXIT"))
		SceneManager::GetInstance().SetActiveScene("BurgerTimeLvl");
}
