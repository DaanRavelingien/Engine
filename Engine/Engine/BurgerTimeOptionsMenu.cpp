#include "EnginePCH.h"
#include "BurgerTimeOptionsMenu.h"
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

void BurgerTimeOptionsMenu::Initialize()
{
	//creating the options lable
	//=============================
	GameObject* pOptionsLable{ new GameObject{"OptionsLabel"} };
	pOptionsLable->AddComponent(new TextRenderComp{});
	pOptionsLable->AddComponent(new TextComp{ "OPTIONS", "Fonts/ARCADECLASSIC.otf", 100,{1,1,1} });

	pOptionsLable->GetTransform()->SetPos({ 230,200,0 });
	pOptionsLable->GetTransform()->SetScale({ 0.5f,0.5f,0.5f });
	AddGameObj(pOptionsLable);

	//creating menu
	//=============

	GameObject* pMenu{ new GameObject{"OptionsMenu"} };
	pMenu->AddComponent(new MenuInputComp{});
	pMenu->AddComponent(new MenuComp{});
	pMenu->AddComponent(new TextureRenderComp{});
	TextureComp* pTextureComp{ new TextureComp{"Textures/BurgerTimeSprites.png"} };
	pTextureComp->SetSourceRect({ 98,145,8,7 });
	pTextureComp->SetDestRect({ 0,0,16,14 });
	pMenu->AddComponent(pTextureComp);

	//MainMenu selection
	//=======================
	GameObject* pMainMenuSelection{ new GameObject{"MainMenuSelection"} };
	pMainMenuSelection->AddComponent(new MenuSelectionMainMenuComp{});
	pMainMenuSelection->AddComponent(new TextRenderComp{});
	pMainMenuSelection->AddComponent(new TextComp{ "MAIN MENU", "Fonts/ARCADECLASSIC.otf", 30,{1,1,1} });
	pMainMenuSelection->GetTransform()->SetPos({ 0, 0, 0 });
	pMenu->AddChild(pMainMenuSelection);

	//Future options will come here

	pMenu->GetTransform()->SetPos({ 230,300,0 });
	AddGameObj(pMenu);
}
