#include "EnginePCH.h"
#include "MenuSelectionExitComp.h"
#include "InputManager.h"

MenuSelectionExitComp::MenuSelectionExitComp()
	:MenuSelectionComp{typeid(this).name()}
{
}

void MenuSelectionExitComp::Activate()
{
	InputManager::GetInstance().QuitGame();
}
