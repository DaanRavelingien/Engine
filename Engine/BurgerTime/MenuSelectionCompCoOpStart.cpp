#include "EnginePCH.h"
#include "MenuSelectionCompCoOpStart.h"
#include <SceneManager.h>

MenuSelectionCompCoOpStart::MenuSelectionCompCoOpStart()
	:MenuSelectionComp{ typeid(this).name() }
{
}

void MenuSelectionCompCoOpStart::Activate()
{
	//set the co op scene as active
	SceneManager::GetInstance().SetActiveScene("BurgerTimeCoOpLvl");

}
