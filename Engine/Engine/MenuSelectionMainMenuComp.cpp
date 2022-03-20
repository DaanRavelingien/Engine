#include "EnginePCH.h"
#include "MenuSelectionMainMenuComp.h"
#include "SceneManager.h"

MenuSelectionMainMenuComp::MenuSelectionMainMenuComp()
	:MenuSelectionComp{typeid(this).name()}
{
}

void MenuSelectionMainMenuComp::Activate()
{
	SceneManager::GetInstance().SetActiveScene("BurgerTimeMainMenu");
}
