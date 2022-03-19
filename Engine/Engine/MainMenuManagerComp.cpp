#include "EnginePCH.h"
#include "MainMenuManagerComp.h"
#include "GameObject.h"
#include "TextComp.h"
#include "MenuPointerComp.h"
#include "SceneManager.h"
#include "InputManager.h"

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
	if (m_SelectedMenuOption.compare("1 PLAYER") == 0)
		SceneManager::GetInstance().SetActiveScene("BurgerTimeLvl");

	if (m_SelectedMenuOption.compare("2 PLAYERS CO OP") == 0)
		SceneManager::GetInstance().SetActiveScene("BurgerTimeLvl");

	if (m_SelectedMenuOption.compare("2 PLAYERS VERSUS") == 0)
		SceneManager::GetInstance().SetActiveScene("BurgerTimeLvl");

	if (m_SelectedMenuOption.compare("OPTIONS") == 0)
		SceneManager::GetInstance().SetActiveScene("BurgerTimeLvl");

	if (m_SelectedMenuOption.compare("EXIT") == 0)
		InputManager::GetInstance().QuitGame();
}
