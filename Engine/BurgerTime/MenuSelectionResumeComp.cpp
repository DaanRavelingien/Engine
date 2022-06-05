#include "EnginePCH.h"
#include "MenuSelectionResumeComp.h"
#include "SceneManager.h"
#include "Scene.h"

MenuSelectionResumeComp::MenuSelectionResumeComp()
	:MenuSelectionComp{ typeid(this).name() }

{
}

void MenuSelectionResumeComp::Activate()
{
	std::string prevSceneName{ SceneManager::GetInstance().GetPrevActiveScene()->GetName()};

	SceneManager::GetInstance().SetActiveScene(prevSceneName);
}
