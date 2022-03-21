#include "EnginePCH.h"
#include "BurgerTimePauseMenu.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "InputManager.h"

//component includes
#include "TransformComp.h"
#include "TextureComp.h"
#include "TextureRenderComp.h"
#include "TextComp.h"
#include "TextRenderComp.h"
#include "MenuInputComp.h"
#include "MenuComp.h"
#include "MenuSelectionExitComp.h"
#include "MenuSelectionStartComp.h"
#include "MenuSelectionMainMenuComp.h"

void BurgerTimePauseMenu::Initialize()
{
	//creating the pause lable
	//=============================
	GameObject* pPauseLable{ new GameObject{"PauseLabel"} };
	pPauseLable->AddComponent(new TextRenderComp{});
	pPauseLable->AddComponent(new TextComp{ "PAUSE", "Fonts/ARCADECLASSIC.otf", 100,{1,1,1} });

	pPauseLable->GetTransform()->SetPos({ 230,200,0 });
	pPauseLable->GetTransform()->SetScale({ 0.5f,0.5f,0.5f });
	AddGameObj(pPauseLable);

	//creating menu
	//=============

	GameObject* pMenu{ new GameObject{"PauseMenu"} };
	pMenu->AddComponent(new MenuInputComp{});
	pMenu->AddComponent(new MenuComp{});
	pMenu->AddComponent(new TextureRenderComp{});
	TextureComp* pTextureComp{ new TextureComp{"Textures/BurgerTimeSprites.png"} };
	pTextureComp->SetSourceRect({ 98,145,8,7 });
	pTextureComp->SetDestRect({ 0,0,16,14 });
	pMenu->AddComponent(pTextureComp);

	//Resume selection
	//==================================
	GameObject* pResumeSelection{ new GameObject{"ResumeSelection"} };
	pResumeSelection->AddComponent(new MenuSelectionStartComp{});
	pResumeSelection->AddComponent(new TextRenderComp{});
	pResumeSelection->AddComponent(new TextComp{ "RESUME", "Fonts/ARCADECLASSIC.otf", 30,{1,1,1} });
	pResumeSelection->GetTransform()->SetPos({ 0, 0, 0 });
	pMenu->AddChild(pResumeSelection);

	//MainMenu selection
	//=======================
	GameObject* pMainMenuSelection{ new GameObject{"MainMenuSelection"} };
	pMainMenuSelection->AddComponent(new MenuSelectionMainMenuComp{});
	pMainMenuSelection->AddComponent(new TextRenderComp{});
	pMainMenuSelection->AddComponent(new TextComp{ "MAIN MENU", "Fonts/ARCADECLASSIC.otf", 30,{1,1,1} });
	pMainMenuSelection->GetTransform()->SetPos({ 0, 40, 0 });
	pMenu->AddChild(pMainMenuSelection);

	//Exit selection
	//==============
	GameObject* pExitSelection{ new GameObject{"ExitSelection"} };
	pExitSelection->AddComponent(new MenuSelectionExitComp{});
	pExitSelection->AddComponent(new TextRenderComp{});
	pExitSelection->AddComponent(new TextComp{ "EXIT", "Fonts/ARCADECLASSIC.otf", 30,{1,1,1} });
	pExitSelection->GetTransform()->SetPos({ 0, 80, 0 });
	pMenu->AddChild(pExitSelection);

	pMenu->GetTransform()->SetPos({ 230,300,0 });
	AddGameObj(pMenu);
}
