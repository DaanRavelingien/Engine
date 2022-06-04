#include "EnginePCH.h"
#include "MenuSelectionVsStartComp.h"
#include <SceneManager.h>

MenuSelectionVsStartComp::MenuSelectionVsStartComp()
	:MenuSelectionComp{ typeid(this).name() }
{
}

void MenuSelectionVsStartComp::Activate()
{
	//set the vs scene as active
	SceneManager::GetInstance().SetActiveScene("BurgerTimeVsLvl");

}
