#include "EnginePCH.h"
#include "MenuSelectionOptionsComp.h"
#include "SceneManager.h"

MenuSelectionOptionsComp::MenuSelectionOptionsComp()
	:MenuSelectionComp{typeid(this).name()}
{
}

void MenuSelectionOptionsComp::Activate()
{
	SceneManager::GetInstance().SetActiveScene("BurgerTimeOptionsMenu");
}
