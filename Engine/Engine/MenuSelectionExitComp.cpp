#include "EnginePCH.h"
#include "MenuSelectionExitComp.h"
#include "InputManager.h"
#include "Scene.h"

MenuSelectionExitComp::MenuSelectionExitComp()
	:MenuSelectionComp{typeid(this).name()}
{
}

void MenuSelectionExitComp::Activate()
{
	m_pGameObj->GetScene()->GetInputManager()->QuitGame();
}
