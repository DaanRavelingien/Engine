#include "EnginePCH.h"
#include "MenuSelectionStartComp.h"
#include "SceneManager.h"

MenuSelectionStartComp::MenuSelectionStartComp()
	:MenuSelectionComp{typeid(this).name()}
{
}

void MenuSelectionStartComp::Activate()
{
	SceneManager::GetInstance().SetActiveScene("BurgerTimeLvl");
}
